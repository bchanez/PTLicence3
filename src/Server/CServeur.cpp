#include "CServeur.hpp"

/*explicit*/ CServeur::CServeur(void)
{
  LOG("CServeur constructor");

  listenerSocket.listen(55001);
  listenerSocket.setBlocking(false);

  udpSocket.setBlocking(false);
  udpSocket.bind(55002);

  fps_timer = 0.f;
}

/*virtual*/ CServeur::~CServeur(void)
{
  LOG("CServeur destructor");
}

// TCP
void CServeur::connection(void)
{
  sf::TcpSocket* client = new sf::TcpSocket;
  if (listenerSocket.accept(*client) == sf::Socket::Done)
  {

      std::cout << "New client connected: " << client->getRemoteAddress() << std::endl;

      client->setBlocking(false);
      clients.push_back(client);
      selector.add(*client);

      Client c;
      c.indice = m_listClient.size();
      c.adresse = client->getRemoteAddress();
      c.port = client->getRemotePort();
      m_listClient.push_back(c);
  }
  else
  {
      delete client;
  }

  for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
  {
      sf::TcpSocket& client = **it;
      sf::Packet packetInitGame;
      dynamic_cast<CActor *>(m_listEntite[m_listClient.size() - 1].get())->setIsCharacter(true);
      packetInitGame << (sf:: Uint16) (m_listClient.size() - 1);
      packetInitGame << (sf:: Uint16) m_DonneesInit.size();
      for(unsigned int i = 0; i < m_DonneesInit.size(); ++i)
        packetInitGame << m_DonneesInit[i];

      while (client.send(packetInitGame) != sf::Socket::Done);

      if(client.receive(packetInitGame) == sf::Socket::Disconnected)
      {
          std::cout<<"Client disconnected"<<std::endl;
          selector.remove(client);
          client.disconnect();
          delete(&client);
          clients.erase(it);
          it--;
      }
  }
}

// UDP
void CServeur::sendUDP(void)
{
  sf::Packet packet;
  packet << (sf:: Uint16) m_listEntite.size();
  for (unsigned int i = 0; i < m_listEntite.size(); ++i)
  {
    struct Donnees donnees = m_listEntite[i].get()->getDonnees();
    donnees.indice =(sf:: Uint16)i;
    packet << donnees;
  }

  for (unsigned int i = 0; i < m_listClient.size(); ++i)
  {
    udpSocket.send(packet, m_listClient[i].adresse, 55003);

  }

  /*for (unsigned int i = 0; i < m_listClient.size(); ++i)
  {
    const char out[] = "Hi, I'm the server";
    if (udpSocket.send(out, sizeof(out), m_listClient[i].adresse, 55003) != sf::Socket::Done)
      return;
  }*/
}

void CServeur::receiveUDP(void)
{
  sf::Packet packet;
  for (unsigned int i = 0; i < m_listClient.size(); ++i)
  {
    struct Donnees donnees;
    sf::IpAddress serveur;
    unsigned short port;
    if(udpSocket.receive(packet, serveur, port) == sf::Socket::Done)
    {
      packet >> donnees;
      std::cout <<
      donnees.keyLeft << " " <<
      donnees.keyRight << " " <<
      donnees.keyUp << " " <<
      donnees.keyDown << " " <<
      donnees.keyShift << std::endl;
      m_listEntite[donnees.indice].get()->setDonnees(donnees);
      std::cout << "marche\n";
    }else
    {
      //std::cout << "marche pas\n";
    }
  }
}

// methode pour la partie
void CServeur::initGame(int taille_carree_map, int nombre_pnj, int nombre_evenement)
{
  m_listEntite.clear();

  // ajout des PNJs
  for(int i = 0; i < nombre_pnj; ++i)
  {
    m_listEntite.push_back(std::make_unique<CActor>());
    m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, taille_carree_map * 40.f), CRandom::floatInRange(0.f, taille_carree_map * 40.f)));
    m_DonneesInit.push_back(m_listEntite[i].get()->getDonneesInit());
  }

  // ajout des evenement
  unsigned int indiceDecalage = m_listEntite.size();
  for(unsigned int i = indiceDecalage; i < nombre_evenement + indiceDecalage; ++i)
  {
    m_listEntite.push_back(std::make_unique<CEvent_pub>());
    m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, taille_carree_map * 40.f), CRandom::floatInRange(0.f, taille_carree_map * 40.f)));
    m_DonneesInit.push_back(m_listEntite[i].get()->getDonneesInit());
  }
}

void CServeur::loopGame(void)
{
  while(1)
  {
    float dt = m_clock.restart().asSeconds();
    fps_timer += dt;


    if (fps_timer >= (1.f/60.f))
    {
      connection();

      // met a jour les events
      for (unsigned int i = 0; i < m_listEntite.size(); ++i)
        m_listEntite[i]->input();

      receiveUDP();
      //std::cout << dt << std::endl;

      sendUDP();
      updateGame(dt);
      fps_timer = 0.f;
    }

    //std::cout<<"test boucle"<<std::endl;
  }
}

void CServeur::updateGame(float dt)
{
  m_DonneesInit.clear();

  //std::cout<<"test update"<<std::endl;
  // update des entites
  for (unsigned int i = 0; i < m_listEntite.size(); ++i)
  {
    m_listEntite[i]->serverUpdate(dt);
    m_DonneesInit.push_back(m_listEntite[i].get()->getDonneesInit());
  }

  //std::cout<<"test update en cours"<<std::endl;

  // update de la profondeur des Entity
  //quickSort(m_listEntite, 0, (int)m_listEntite.size() - 1);
  //std::cout<<"test update fin"<<std::endl;
}

// trie rapide des entites par rapport a leurs positions sur l'axe y
void CServeur::quickSort(std::vector<std::unique_ptr<CEntity>>& tableau, int debut, int fin)
{
    int gauche = debut-1;
    int droite = fin+1;
    const float pivot = tableau[debut]->getPosition().y;

    if(debut >= fin)
        return;

    while(1)
    {
        do droite--; while(tableau[droite]->getPosition().y > pivot);
        do gauche++; while(tableau[gauche]->getPosition().y < pivot);

        if(gauche < droite)
        {
          std::swap(tableau[gauche], tableau[droite]);
        }
        else break;
    }

    quickSort(tableau, debut, droite);
    quickSort(tableau, droite+1, fin);
}
