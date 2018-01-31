#include "CServeur.hpp"

/*explicit*/ CServeur::CServeur(void)
{
  LOG("CServeur constructor\n");

  listenerSocket.listen(55001);   //Pour le TCP
  listenerSocket.setBlocking(false);  //Ne va pas attendre une réponse

  udpSocket.setBlocking(false);   //Idem
  udpSocket.bind(55002);

  fps_timer = 0.f;    //Temps de boucle (temps de refresh)
}

/*virtual*/ CServeur::~CServeur(void)
{
  LOG("CServeur destructor\n");
}

// TCP
void CServeur::connection(void)
{
  sf::TcpSocket* client = new sf::TcpSocket;    //Varable client (client qui va se connecter)
  if (listenerSocket.accept(*client) == sf::Socket::Done)
  {
    std::cout << "New client connected: " << client->getRemoteAddress() << std::endl;
    client->setBlocking(false);               //Mettre en non bloquant (éviter de ralentir le serveur)

    // Cree un client (Voir struct Client CServeur.hpp)
    Client c;
    c.etat = 0;
    c.socketTCP = client;
    c.indice = m_listClient.size();     //Indice du client (1er client sera le PNJ 0, 2eme sera le PNJ 1 etc...)
    c.adresse = client->getRemoteAddress();
    c.port = client->getRemotePort();
    for(unsigned int i = 0; i < m_everyDonnees.size(); ++i)
      c.synchroPosition.push_back(0);     //Pour chaque client, on met a jour la position des clients tout les 8 frames

    m_listClient.push_back(c);
  }
  else
  {
    delete client;    //Client n'a pas réussi à se connecter
  }
}

// UDP
void CServeur::send(void)
{
  for (unsigned int i = 0; i < m_listClient.size(); ++i) //Pour tout les clients du tableau ajouté précedemment
  {
    switch(m_listClient.at(i).etat)  // Etat dess clients (créer la partie, en cours de jeu, reviens d'un état pause; )
    {
      case 0 : // envoie donnees d'initialisation de partie envoyer tout (position, CActor, Events) dans un tableau
      {
        // initialisation des donnees
        std::cout << "le serveur envoie au client " << m_listClient.at(i).indice << " les donnees d'init de partie" << std::endl;
        sf::Packet packetInitGame;
        dynamic_cast<CActor *>(m_listEntite[m_listClient.at(i).indice].get())->setIsCharacter(true);
        packetInitGame << (sf:: Uint16) (m_listClient.at(i).indice);
        packetInitGame << (sf:: Uint16) m_donneesInit.size(); //Taille du tableau
        for(unsigned int i = 0; i < m_donneesInit.size(); ++i) //Envoi du tableau
          packetInitGame << m_donneesInit.at(i);

        // envoie
        while (m_listClient.at(i).socketTCP->send(packetInitGame) != sf::Socket::Done);  //Envoi données en TCP (while pour tout envoyer) While pour bien tout envoyer

        m_listClient.at(i).etat = 1; //Ne fait plus rien
        break;
      }
      case 1 : // nothing
      {
        break;
      }
      case 2 : // envoi donnes normales (indice entité, état)
      {
        sf::Packet packet;
        packet << (sf:: Uint16) m_listClient.at(i).donnees.size(); //Met la taille dans le paquet
        for(unsigned int j = 0; j < m_listClient.at(i).donnees.size(); ++j)
          packet << m_listClient.at(i).donnees[j];                 //Tableau dans le paquet

        udpSocket.send(packet, m_listClient.at(i).adresse, 55003);    //Envoi
        break;
      }
      case 3 : // envoie de toutes les donnees a synchro (debut de partie au pause) Tant que ça tourne, on va augmenter l'indice de synchro, si l'indice dépasse 8, on synchro
      {
        m_listClient.at(i).donnees.clear();

        for(unsigned int j = 0; j < m_everyDonnees.size(); ++j)
        {
          if(m_listClient.at(i).synchroPosition[j] >= 8)
          {
              m_listClient.at(i).donnees.push_back(m_everyDonnees[j]);
              m_listClient.at(i).donnees[m_listClient.at(i).donnees.size() - 1].mustUpdatePosition = true;
              m_listClient.at(i).synchroPosition[j] = 0;   //Eviter d'envoyer tout le temps
          }
        }

        sf::Packet packet;
        packet << (sf:: Uint16) m_listClient.at(i).donnees.size();
        for(unsigned int j = 0; j < m_listClient.at(i).donnees.size(); ++j)
          packet << m_listClient.at(i).donnees[j];

        udpSocket.send(packet, m_listClient.at(i).adresse, 55003);

        m_listClient.at(i).etat = 2; //Il est en jeu
        break;
      }
      default :
      {
        std::cout << "PROBLEME le client " << m_listClient.at(i).indice << " est a l'etat " << m_listClient.at(i).etat << std::endl; //Debug
        break;
      }
    }

    m_listClient.at(i).donnees.clear(); //Supprime tout
  }

  m_donneesInit.clear(); //Supprime les données d'initialisation de partie (une fois que c'est envoyé ou à chaque tour de frame)
}

void CServeur::receive(void)  //recoie
{
  for (unsigned int i = 0; i < m_listClient.size(); ++i)
  {
    sf::Packet packet;
    struct Donnees donnees;
    sf::IpAddress serveur;
    unsigned short port;

    // recoie donnees de mise a jour des inputs du client
    if(udpSocket.receive(packet, serveur, port) == sf::Socket::Done)
    {
      packet >> donnees; //Recoie le paquet

      try {
        m_listEntite.at(donnees.indice).get()->setDonnees(donnees);
      }
      catch (std::exception const& e){
        std::cout << "Error : " << e.what() << std::endl;
      }
    }

    // recoie un ordre du client (client veut changer d'état)
    if (m_listClient.at(i).socketTCP->receive(packet) == sf::Socket::Done)
    {
      sf:: Uint16 etat;
      packet >> etat;
      std::cout << "le client " << m_listClient.at(i).indice << " se passe a l'etat " << etat << std::endl;
      m_listClient.at(i).etat = etat;
    }

    // detruit client si deconnecte
    if(m_listClient.at(i).socketTCP->receive(packet) == sf::Socket::Disconnected)
    {
       std::cout<<"Client disconnected"<<std::endl;
       m_listClient.at(i).socketTCP->disconnect();
       delete(m_listClient.at(i).socketTCP);
       m_listClient.erase(m_listClient.begin() + i);
       i--;
       break;
    }
  }
}

// methode pour la partie
void CServeur::initGame(int nombre_pnj, int nombre_evenement)
{
  m_listEntite.clear(); //Clear le tableau

  // ajout des PNJs
  for(int i = 0; i < nombre_pnj; ++i)
  {
    m_listEntite.push_back(std::make_unique<CActor>(i, &m_listEntite));
    m_listEntite.at(i).get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, SIZE_MAP_X*SIZE_TILE), CRandom::floatInRange(0.f, SIZE_MAP_Y*SIZE_TILE))); // PNJ Apparait à tel endroit
    m_donneesInit.push_back(m_listEntite.at(i).get()->getDonneesInit()); //On ajoute les données de base quand on créer la partie
    m_everyDonnees.push_back(m_listEntite.at(i).get()->getDonnees()); // Données actuelles
  }

  // ajout des evenement
  unsigned int indiceDecalage = m_listEntite.size();
  for(unsigned int i = indiceDecalage; i < nombre_evenement + indiceDecalage; ++i)
  {
    m_listEntite.push_back(std::make_unique<CEvent_pub>(i, &m_listEntite)); //Pub (éviter d'avoir deux pointeurs sur le même objet)
    m_listEntite.at(i).get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, SIZE_MAP_X*SIZE_TILE), CRandom::floatInRange(0.f, SIZE_MAP_Y*SIZE_TILE)));
    m_donneesInit.push_back(m_listEntite.at(i).get()->getDonneesInit());
    m_everyDonnees.push_back(m_listEntite.at(i).get()->getDonnees());
  }
}

void CServeur::loopServer(void)
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
        for (unsigned int i = 0; i < m_listEntite.size(); ++i){
          try {
            m_listEntite.at(i)->input();
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

void CServeur::updateGame(float dt)
{
  // update des entites
  for (unsigned int i = 0; i < m_listEntite.size(); ++i) //Parcours tout le tableau d'entité (pub, PNJ, etc...)
  {
    // suppression des CActor qui doivent disparaitre
    if (m_listEntite.at(i)->getDonneesInit().classe == "CActor" && dynamic_cast<CActor *>(m_listEntite.at(i).get())->getMustDisappear()) //Seul CActor peut disparaître
    {
      std::cout  << "delete \n";
      m_listEntite.erase(m_listEntite.begin() + i); //Supprime de la liste
      m_everyDonnees.erase(m_everyDonnees.begin() + i);
      for (unsigned int j = 0; j < m_listClient.size(); ++j)
        m_listClient[j].synchroPosition.erase(m_listClient[j].synchroPosition.begin() + i); //Supprime de chaque tableau de chaque client
    }

    m_listEntite.at(i)->update(true, dt);

    // met a jour les donnees d'envoie pour la creation d'une partie si un joueur se connecte
    m_donneesInit.push_back(m_listEntite.at(i).get()->getDonneesInit());

    // met a jour les donnees d'envois courantes
    if(m_everyDonnees.at(i) != m_listEntite.at(i).get()->getDonnees()) //Si un joueur se connecte, il aura ces infos là
    {
      m_everyDonnees.at(i) = m_listEntite.at(i).get()->getDonnees();
      for (unsigned int j = 0; j < m_listClient.size(); ++j)
      {
        m_listClient[j].donnees.push_back(m_everyDonnees.at(i));
        m_listClient[j].synchroPosition.at(i)++;
        if(m_listClient[j].synchroPosition.at(i) >= 8)
        {
            m_listClient[j].donnees[m_listClient[j].donnees.size() - 1].mustUpdatePosition = true;
            if (m_listClient[j].etat == 2)
              m_listClient[j].synchroPosition.at(i) = 0;
        }
      }
    }
  }
}
