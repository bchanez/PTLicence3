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
}

// UDP
void CServeur::send(void)
{
  // initialisation des donnees normal
  sf::Packet packet;
  std::vector<struct Donnees> listeDonnees;

  for (unsigned int i = 0; i < m_listEntite.size(); ++i)
  {
    if(m_Donnees[i] != m_listEntite[i].get()->getDonnees())
    {
      m_Donnees[i] = m_listEntite[i].get()->getDonnees();

      m_synchroPosition[i]++;
      if(m_synchroPosition[i] == 8)
      {
        m_Donnees[i].mustUpdatePosition = true;
        m_synchroPosition[i] = 0;
      }

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
    switch(m_listClient[i].etat)
    {
      case 0 : // envoie donnees d'initialisation de partie
      {
        // initialisation des donnees
        std::cout << "le serveur envoie au client " << m_listClient[i].indice << " les donnees d'init de partie" << std::endl;
        sf::Packet packetInitGame;
        dynamic_cast<CActor *>(m_listEntite[m_listClient[i].indice].get())->setIsCharacter(true);
        packetInitGame << (sf:: Uint16) (m_listClient[i].indice);
        packetInitGame << (sf:: Uint16) m_DonneesInit.size();
        for(unsigned int i = 0; i < m_DonneesInit.size(); ++i)
          packetInitGame << m_DonneesInit[i];

        // envoie
        while (m_listClient[i].socketTCP->send(packetInitGame) != sf::Socket::Done);

        m_listClient[i].etat = 99;
        break;
      }
      case 1 : // envoie donnes normal
      {
        udpSocket.send(packet, m_listClient[i].adresse, 55003);
        break;
      }
      case 99 : // do nothing
      {
        break;
      }
      default :
      {
        std::cout << "PROBLEME le client " << m_listClient[i].indice << " est a l'etat " << m_listClient[i].etat << std::endl;
        break;
      }
    }
  }
}

void CServeur::receive(void)
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
      packet >> donnees;
      m_listEntite[donnees.indice].get()->setDonnees(donnees);
    }

    // recoie un ordre du client
    if (m_listClient[i].socketTCP->receive(packet) == sf::Socket::Done)
    {
      sf:: Uint16 etat;
      packet >> etat;
      std::cout << "le client " << m_listClient[i].indice << " se passe a l'etat " << etat << std::endl;
      m_listClient[i].etat = etat;
    }

    // detruit client si deconnecte
    if(m_listClient[i].socketTCP->receive(packet) == sf::Socket::Disconnected)
    {
       std::cout<<"Client disconnected"<<std::endl;
       m_listClient[i].socketTCP->disconnect();
       delete(m_listClient[i].socketTCP);
       m_listClient.erase(m_listClient.begin() + i);
       i--;
       break;
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
    m_synchroPosition.push_back(0);
  }

  // ajout des evenement
  unsigned int indiceDecalage = m_listEntite.size();
  for(unsigned int i = indiceDecalage; i < nombre_evenement + indiceDecalage; ++i)
  {
    m_listEntite.push_back(std::make_unique<CEvent_pub>(i));
    m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, SIZE_MAP_X*SIZE_TILE), CRandom::floatInRange(0.f, SIZE_MAP_Y*SIZE_TILE)));
    m_DonneesInit.push_back(m_listEntite[i].get()->getDonneesInit());
    m_Donnees.push_back(m_listEntite[i].get()->getDonnees());
    m_synchroPosition.push_back(0);
  }
}

void CServeur::loopServer(void)
{
  initGame(NB_PNJ, NB_STAND);

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

      receive();
      send();

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
