#include "CServeur.hpp"

/*explicit*/ CServeur::CServeur(void)
{
  LOG("CServeur constructor\n");

  listenerSocket.listen(55001);
  listenerSocket.setBlocking(false);

  udpSocket.setBlocking(false);
  udpSocket.bind(55002);

  fps_timer = 0.f;
}

/*virtual*/ CServeur::~CServeur(void)
{
  LOG("CServeur destructor\n");
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
    for(unsigned int i = 0; i < m_everyDonnees.size(); ++i)
      c.synchroPosition.push_back(0);

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
        packetInitGame << (sf:: Uint16) m_donneesInit.size();
        for(unsigned int i = 0; i < m_donneesInit.size(); ++i)
          packetInitGame << m_donneesInit[i];

        // envoie
        while (m_listClient[i].socketTCP->send(packetInitGame) != sf::Socket::Done);

        m_listClient[i].etat = 1;
        break;
      }
      case 1 : // nothing
      {
        break;
      }
      case 2 : // envoie donnes normal
      {
        // initialisation des donnees normal
        for(unsigned int j = 0; j < m_everyDonnees.size(); ++j)
        {
          m_donnees.push_back(m_everyDonnees[j]);
          if(m_listClient[i].synchroPosition[j] >= 8)
          {
              m_donnees[m_donnees.size() - 1].mustUpdatePosition = true;
              m_listClient[i].synchroPosition[j] = 0;
          }
        }

        sf::Packet packet;
        packet << (sf:: Uint16) m_donnees.size();
        for(unsigned int j = 0; j < m_donnees.size(); ++j)
          packet << m_donnees[j];

        udpSocket.send(packet, m_listClient[i].adresse, 55003);
        break;
      }
      default :
      {
        std::cout << "PROBLEME le client " << m_listClient[i].indice << " est a l'etat " << m_listClient[i].etat << std::endl;
        break;
      }
    }
  }

  m_donneesInit.clear();
  m_donnees.clear();
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
    m_donneesInit.push_back(m_listEntite[i].get()->getDonneesInit());
    m_everyDonnees.push_back(m_listEntite[i].get()->getDonnees());
  }

  // ajout des evenement
  unsigned int indiceDecalage = m_listEntite.size();
  for(unsigned int i = indiceDecalage; i < nombre_evenement + indiceDecalage; ++i)
  {
    m_listEntite.push_back(std::make_unique<CEvent_pub>(i));
    m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, SIZE_MAP_X*SIZE_TILE), CRandom::floatInRange(0.f, SIZE_MAP_Y*SIZE_TILE)));
    m_donneesInit.push_back(m_listEntite[i].get()->getDonneesInit());
    m_everyDonnees.push_back(m_listEntite[i].get()->getDonnees());
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
  // update des entites
  for (unsigned int i = 0; i < m_listEntite.size(); ++i)
  {
    // suppression des CActor qui doivent disparaitre
    if (m_listEntite[i]->getDonneesInit().classe == "CActor" && dynamic_cast<CActor *>(m_listEntite[i].get())->getMustDisappear())
    {
      std::cout  << "delete \n";
      m_listEntite.erase(m_listEntite.begin() + i);
      m_everyDonnees.erase(m_everyDonnees.begin() + i);
      for (unsigned int j = 0; j < m_listClient.size(); ++j)
        m_listClient[j].synchroPosition.erase(m_listClient[j].synchroPosition.begin() + i);
    }

    m_listEntite[i]->update(true, dt);

    // met a jour les donnees d'envoie pour la creation d'une partie si un joueur se connecte
    m_donneesInit.push_back(m_listEntite[i].get()->getDonneesInit());

    // met a jour les donnees d'envoie courrante
    if(m_everyDonnees[i] != m_listEntite[i].get()->getDonnees())
    {
      m_everyDonnees[i] = m_listEntite[i].get()->getDonnees();
      for (unsigned int j = 0; j < m_listClient.size(); ++j)
        m_listClient[j].synchroPosition[i]++;
    }
  }
}
