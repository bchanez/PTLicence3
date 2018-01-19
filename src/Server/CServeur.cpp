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

    // cree un client
    Client c;
    c.etat = 0;
    c.socketTCP = client;
    c.indice = m_listClient.size();
    c.adresse = client->getRemoteAddress();
    c.port = client->getRemotePort();
    m_listClient.push_back(c);
  }
  else
  {
    delete client;
  }

  for (unsigned int i = 0; i < m_listClient.size(); ++i)
  {
    if (m_listClient[i].etat == 0)
    {
      // envoie les info au client pour creer la partie
      sf::Packet packetInitGame;
      dynamic_cast<CActor *>(m_listEntite[m_listClient.size() - 1].get())->setIsCharacter(true);
      packetInitGame << (sf:: Uint16) (m_listClient.size() - 1);
      packetInitGame << (sf:: Uint16) m_DonneesInit.size();
      for(unsigned int i = 0; i < m_DonneesInit.size(); ++i)
        packetInitGame << m_DonneesInit[i];

      while (m_listClient[i].socketTCP->send(packetInitGame) != sf::Socket::Done);

      m_listClient[i].etat = 1;
    }


    sf::Packet packet;
    // recoie info client en tcp
    if (m_listClient[i].socketTCP->receive(packet) == sf::Socket::Done)
    {
      sf:: Uint16 etat;
      packet >> etat;
      std::cout << " etat : " << etat << std::endl;
      m_listClient[i].etat = etat;
    }

    // detruit client si deconnecte
    if(m_listClient[i].socketTCP->receive(packet) == sf::Socket::Disconnected)
    { exit(0);
       std::cout<<"Client disconnected"<<std::endl;
       m_listClient[i].socketTCP->disconnect();
       delete(m_listClient[i].socketTCP);
       m_listClient.erase(m_listClient.begin() + i);
       i--;
    }
  }
}

// UDP
void CServeur::sendUDP(void)
{
  sf::Packet packet;
  std::vector<struct Donnees> listeDonnees;

  for (unsigned int i = 0; i < m_listEntite.size(); ++i)
  {
    if(m_Donnees[i] != m_listEntite[i].get()->getDonnees())
    {
      m_Donnees[i] = m_listEntite[i].get()->getDonnees();
      listeDonnees.push_back(m_Donnees[i]);
    }
  }

  packet << (sf:: Uint16) listeDonnees.size();
  for(unsigned int i = 0; i < listeDonnees.size(); ++i)
  {
    packet << listeDonnees[i];
  }

  for (unsigned int i = 0; i < m_listClient.size(); ++i)
  {
    if(m_listClient[i].etat == 2)
    {
      std::cout << "envoieDonne\n";
      udpSocket.send(packet, m_listClient[i].adresse, 55003);
    }
  }
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
      m_listEntite[donnees.indice].get()->setDonnees(donnees);
    }
  }
}

// methode pour la partie
void CServeur::initGame(int nombre_pnj, int nombre_evenement)
{
  m_listEntite.clear();

  // ajout des PNJs
  for(int i = 0; i < nombre_pnj; ++i)
  {
    m_listEntite.push_back(std::make_unique<CActor>(i, &m_listEntite));
    m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, SIZE_MAP_X*SIZE_TILE), CRandom::floatInRange(0.f, SIZE_MAP_Y*SIZE_TILE)));
    m_DonneesInit.push_back(m_listEntite[i].get()->getDonneesInit());
    m_Donnees.push_back(m_listEntite[i].get()->getDonnees());
  }

  // ajout des evenement
  unsigned int indiceDecalage = m_listEntite.size();
  for(unsigned int i = indiceDecalage; i < nombre_evenement + indiceDecalage; ++i)
  {
    m_listEntite.push_back(std::make_unique<CEvent_pub>(i));
    m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, SIZE_MAP_X*SIZE_TILE), CRandom::floatInRange(0.f, SIZE_MAP_Y*SIZE_TILE)));
    m_DonneesInit.push_back(m_listEntite[i].get()->getDonneesInit());
    m_Donnees.push_back(m_listEntite[i].get()->getDonnees());
  }
}

void CServeur::loopGame(void)
{
  while(1)
  {
    float dt = m_clock.restart().asSeconds();
    fps_timer += dt;

    if (fps_timer >= (1.f/70.f))
    {
      connection();

      // met a jour les events
      for (unsigned int i = 0; i < m_listEntite.size(); ++i)
        m_listEntite[i]->input();

      receiveUDP();
      sendUDP();

      updateGame(fps_timer);
      fps_timer = 0.f;
    }
  }
}

void CServeur::updateGame(float dt)
{
  m_DonneesInit.clear();

  // update des entites
  for (unsigned int i = 0; i < m_listEntite.size(); ++i)
  {
    m_listEntite[i]->update(true, dt);
    m_DonneesInit.push_back(m_listEntite[i].get()->getDonneesInit());
  }
}
