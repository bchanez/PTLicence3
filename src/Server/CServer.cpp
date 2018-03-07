#include "CServer.hpp"

/*explicit*/ CServer::CServer(void)
{
  LOG("CServer constructor\n");

  listenerSocket.listen(55001);   //Pour le TCP
  listenerSocket.setBlocking(false);  //Ne va pas attendre une réponse

  udpSocket.setBlocking(false);   //Idem
  udpSocket.bind(55002);

  fps_timer = 0.f;    //Temps de boucle (temps de refresh)
}

/*virtual*/ CServer::~CServer(void)
{
  LOG("CServer destructor\n");
}

// TCP
void CServer::connection(void)
{
  sf::TcpSocket* client = new sf::TcpSocket;    //Varable client (client qui va se connecter)
  if (listenerSocket.accept(*client) == sf::Socket::Done)
  {
    client->setBlocking(false);               //Mettre en non bloquant (éviter de ralentir le serveur)

    //test si client c'est deja connecte a la partie
    bool exist = false;
    for (unsigned int i = 0; i < m_listClient.size(); ++i)
    {
      if(client->getRemoteAddress() == m_listClient.at(i).adress)
      {
        std::cout << "Client " <<  m_listClient.at(i).index << " reconnected" << std::endl;
        std::cout << "le client " << m_listClient.at(i).index << " passe a l'etat 0" << std::endl;
        exist = true;
        m_listClient.at(i).state = 0;
        m_listClient.at(i).socketTCP = client;
        break;
      }
    }

    // Cree un client si nouveau client (Voir struct Client CServeur.hpp)

    if(!exist)
    {
      std::cout << "New client connected: " << client->getRemoteAddress() << std::endl;
      Client c;
      c.state = 0;
      c.result = "";
      c.socketTCP = client;
      c.index = m_listClient.size();     //Indice du client (1er client sera le PNJ 0, 2eme sera le PNJ 1 etc...)
      c.adress = client->getRemoteAddress();
      c.port = client->getRemotePort();
      for(unsigned int i = 0; i < m_everyData.size(); ++i)
        c.synchroPosition.push_back(0);     //Pour chaque client, on met a jour la position des clients tout les 8 frames

      m_listClient.push_back(c);
    }
  }
  else
  {
    delete client;    //Client n'a pas réussi à se connecter
  }
}

// UDP
void CServer::send(void)
{
  for (unsigned int i = 0; i < m_listClient.size(); ++i) //Pour tout les clients du tableau ajouté précedemment
  {
    switch(m_listClient.at(i).state)  // Etat dess clients (créer la partie, en cours de jeu, reviens d'un état pause; )
    {
      case 0 : // envoie donnees d'initialisation de partie envoyer tout (position, CActor, Events) dans un tableau
      {
        // initialisation des donnees
        std::cout << "le serveur envoie au client " << m_listClient.at(i).index << " les donnees d'init de partie" << std::endl;
        sf::Packet packetInitGame;
        dynamic_cast<CActor *>(m_listEntities[m_listClient.at(i).index].get())->setIsCharacter(true);
        packetInitGame <<  m_listClient.at(i).result;
        packetInitGame << (sf:: Uint16) (m_listClient.at(i).index);
        packetInitGame << (sf:: Uint16) m_dataInit.size(); //Taille du tableau
        for(unsigned int i = 0; i < m_dataInit.size(); ++i) //Envoi du tableau
          packetInitGame << m_dataInit.at(i);

        // envoie
        while (m_listClient.at(i).socketTCP->send(packetInitGame) != sf::Socket::Done);  //Envoi données en TCP (while pour tout envoyer) While pour bien tout envoyer

        std::cout << "le client " << m_listClient.at(i).index << " passe a l'etat 1" << std::endl;
        m_listClient.at(i).state = 1; //Ne fait plus rien
        break;
      }
      case 1 : // nothing
      {
        break;
      }
      case 2 : // envoi donnes normales (indice entité, état)
      {
        sf::Packet packet;
        packet << (sf:: Uint16) m_listClient.at(i).data.size(); //Met la taille dans le paquet
        for(unsigned int j = 0; j < m_listClient.at(i).data.size(); ++j)
          packet << m_listClient.at(i).data[j];                 //Tableau dans le paquet

        udpSocket.send(packet, m_listClient.at(i).adress, 55003);    //Envoi
        break;
      }
      case 3 : // envoie de toutes les donnees a synchro (debut de partie au pause) Tant que ça tourne, on va augmenter l'indice de synchro, si l'indice dépasse 8, on synchro
      {
        m_listClient.at(i).data.clear();

        for(unsigned int j = 0; j < m_everyData.size(); ++j)
        {
          if(m_listClient.at(i).synchroPosition[j] >= 8)
          {
              m_listClient.at(i).data.push_back(m_everyData[j]);
              m_listClient.at(i).data[m_listClient.at(i).data.size() - 1].mustUpdatePosition = true;
              m_listClient.at(i).synchroPosition[j] = 0;   //Eviter d'envoyer tout le temps
          }
        }

        sf::Packet packet;
        packet << (sf:: Uint16) m_listClient.at(i).data.size();
        for(unsigned int j = 0; j < m_listClient.at(i).data.size(); ++j)
          packet << m_listClient.at(i).data[j];

        udpSocket.send(packet, m_listClient.at(i).adress, 55003);

        std::cout << "le client " << m_listClient.at(i).index << " passe a l'etat 2" << std::endl;
        m_listClient.at(i).state = 2; //Il est en jeu
        break;
      }
      default :
      {
        std::cout << "PROBLEME le client " << m_listClient.at(i).index << " est a l'etat " << m_listClient.at(i).state << std::endl; //Debug
        break;
      }
    }

    m_listClient.at(i).data.clear(); //Supprime tout
  }

  m_dataInit.clear(); //Supprime les données d'initialisation de partie (une fois que c'est envoyé ou à chaque tour de frame)
}

void CServer::receive(void)  //recoie
{
  for (unsigned int i = 0; i < m_listClient.size(); ++i)
  {
    sf::Packet packet;
    struct Data data;
    sf::IpAddress server;
    unsigned short port;

    // recoie donnees de mise a jour des inputs du client
    if(udpSocket.receive(packet, server, port) == sf::Socket::Done)
    {
      packet >> data; //Recoie le paquet
      try {
        m_listEntities.at(data.index).get()->setData(data);
      }
      catch (std::exception const& e){
        std::cout << "------------------------ Error : " << e.what() << std::endl;
      }
    }

    // recoie un ordre du client (client veut changer d'état)
    if (m_listClient.at(i).socketTCP->receive(packet) == sf::Socket::Done)
    {
      sf:: Uint16 state;
      packet >> state;
      std::cout << "le client " << m_listClient.at(i).index << " se passe a l'etat " << state << std::endl;
      m_listClient.at(i).state = state;
    }

    // deconnecte client si deconnecte
    if(m_listClient.at(i).socketTCP->receive(packet) == sf::Socket::Disconnected)
    {
       std::cout<<"Client " << m_listClient.at(i).index << " disconnected"<<std::endl;
       dynamic_cast<CActor *>(m_listEntities[m_listClient.at(i).index].get())->setIsCharacter(false);
       m_listClient.at(i).socketTCP->disconnect();
       break;
    }
  }
}

// methode pour la partie
void CServer::initGame(int nb_npc, int nb_event)
{
  m_listEntities.clear(); //Clear le tableau

  // ajout des PNJs
  for(int i = 0; i < nb_npc; ++i)
  {
    m_listEntities.push_back(std::make_unique<CActor>(i, &m_listEntities));
    m_listEntities.at(i).get()->setPosition(sf::Vector2f(CRandom::floatInRange(SIZE_TILE, (SIZE_MAP_X-1)*SIZE_TILE), CRandom::floatInRange(SIZE_TILE, (SIZE_MAP_Y-1)*SIZE_TILE))); // PNJ Apparait à tel endroit
    m_dataInit.push_back(m_listEntities.at(i).get()->getDataInit()); //On ajoute les données de base quand on créer la partie
    m_everyData.push_back(m_listEntities.at(i).get()->getData()); // Données actuelles
  }

  // ajout des evenement
  unsigned int shiftIndex = m_listEntities.size();
  for(unsigned int i = shiftIndex; i < nb_event + shiftIndex; ++i)
  {
    m_listEntities.push_back(std::make_unique<CEvent_pub>(i, &m_listEntities)); //Pub (éviter d'avoir deux pointeurs sur le même objet)

    //evite d'avoir 2 pubs au meme endroit
    float positionX = 0;
    float positionY = 0;
    bool collision = false;

    do
    {
      positionX = CRandom::floatInRange(SIZE_TILE*2, (SIZE_MAP_X-2)*SIZE_TILE);
      positionY = CRandom::floatInRange(SIZE_TILE*2, (SIZE_MAP_Y-2)*SIZE_TILE);

      collision = false;
      for(unsigned int j = shiftIndex; j < m_listEntities.size(); ++j)
      {
        if(m_listEntities.size() - shiftIndex >= 2 &&
        CCollision::collision(
          sf::FloatRect(m_listEntities.at(j).get()->getPosition().x, m_listEntities.at(j).get()->getPosition().y, 200.f, 160.f),
          sf::FloatRect(positionX, positionY, 200.f, 160.f)))
        {
          collision = true;
        }
      }
    }while (collision);

    m_listEntities.at(i).get()->setPosition(sf::Vector2f(positionX, positionY));
    m_dataInit.push_back(m_listEntities.at(i).get()->getDataInit());
    m_everyData.push_back(m_listEntities.at(i).get()->getData());
  }
}

void CServer::loopServer(void)
{
  initGame(NB_PNJ, NB_STAND); //init PNJ et Stands

  while(1)
  {

      float dt = m_clock.restart().asSeconds();
      fps_timer += dt;

      if (fps_timer >= (1.f/70.f)) //Limiter les FPS
      {
        connection(); //Connecter les clients

        // met a jour les events
        for (unsigned int i = 0; i < m_listEntities.size(); ++i){
          try {
            m_listEntities.at(i)->input();
          }
          catch (std::exception const& e){
            std::cout << "Error : " << e.what() << std::endl;
          }
        }

        receive();
        send();

        updateGame(fps_timer);
        fps_timer = 0.f; //reset FPS
      }
  }
}

void CServer::updateGame(float dt)
{
  // update des entites
  int numberCActor = 0;
  for (unsigned int i = 0; i < m_listEntities.size(); ++i) //Parcours tout le tableau d'entité (pub, PNJ, etc...)
  {
    // suppression des CActor qui doivent disparaitre
    if (m_listEntities.at(i)->getDataInit().cclass == "CActor")
    {
      numberCActor++;
      if(dynamic_cast<CActor *>(m_listEntities.at(i).get())->getMustDisappear()) //Seul CActor peut disparaître
      {
        std::cout  << "delete \n";
        m_listEntities.erase(m_listEntities.begin() + i); //Supprime de la liste
        m_everyData.erase(m_everyData.begin() + i);

        for (unsigned int j = 0; j < m_listClient.size(); ++j)
        {
          if(m_listClient[j].index == i)
            m_listClient[j].result = "lose";

          m_listClient[j].synchroPosition.erase(m_listClient[j].synchroPosition.begin() + i); //Supprime de chaque tableau de chaque client
        }
      }
    }

    m_listEntities.at(i)->update(true, dt);

    // met a jour les donnees d'envoie pour la creation d'une partie si un joueur se connecte
    m_dataInit.push_back(m_listEntities.at(i).get()->getDataInit());

    // met a jour les donnees d'envois courantes
    if(m_everyData.at(i) != m_listEntities.at(i).get()->getData()) //Si un joueur se connecte, il aura ces infos là
    {
      m_everyData.at(i) = m_listEntities.at(i).get()->getData();
      for (unsigned int j = 0; j < m_listClient.size(); ++j)
      {
        m_listClient[j].data.push_back(m_everyData.at(i));
        m_listClient[j].synchroPosition.at(i)++;
        if(m_listClient[j].synchroPosition.at(i) >= 8)
        {
            m_listClient[j].data[m_listClient[j].data.size() - 1].mustUpdatePosition = true;
            if (m_listClient[j].state == 2)
              m_listClient[j].synchroPosition.at(i) = 0;
        }
      }
    }
  }

  for (unsigned int j = 0; j < m_listClient.size(); ++j)
    if (numberCActor == 1 && m_listClient[j].result != "lose")
      m_listClient[j].result = "win";
}
