#include "CServeur.hpp"

/*explicit*/ CServeur::CServeur(void)
{
  LOG("CServeur constructor");

  listenerSocket.listen(12345);
  listenerSocket.setBlocking(false);
  selector.add(listenerSocket);

  udpSocket.setBlocking(false);
  udpSocket.bind(55002);
}

/*virtual*/ CServeur::~CServeur(void)
{
  LOG("CServeur destructor");
}

// TCP
void CServeur::connection(void)
{
  if (selector.wait())
  {
      if (selector.isReady(listenerSocket))
      {
          sf::TcpSocket* client = new sf::TcpSocket;
          if (listenerSocket.accept(*client) == sf::Socket::Done)
          {

              std::cout << "New client connected: " << client->getRemoteAddress() << ":" << client->getRemotePort() << std::endl;

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
      }
      else
      {
          for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
          {
              sf::TcpSocket& client = **it;
              if (selector.isReady(client))
              {
                // Receive a message back from the client
                std::string str;
                sf::Packet p;

                client.receive(p);
                p >> str;
                std::cout << "The client said: " << str << std::endl;

/*
                  sf::Packet packetInitGame;

                  packetInitGame << (sf:: Uint16) m_listClient.size();
                  for(unsigned int i = 0; i < m_DonneesInit.size(); ++i)
                    packetInitGame << m_DonneesInit[i];

                  while (client.send(packetInitGame) != sf::Socket::Done);
*/
              }
              if(client.receive(packet) == sf::Socket::Disconnected)
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
  }
}

// UDP
void CServeur::sendUDP(void)
{
  for (unsigned int i = 0; i < m_listClient.size(); ++i)
  {
    udpSocket.send(packet, m_listClient[i].adresse, m_listClient[i].port);
  }
}

void CServeur::receiveUDP(void)
{
  for (unsigned int i = 0; i < m_listClient.size(); ++i)
  {
    udpSocket.receive(packet, m_listClient[i].adresse, m_listClient[i].port);
  }
}

// methode pour la partie
void CServeur::initGame(int taille_carree_map, int nombre_pnj, int nombre_evenement)
{
  m_listEntite.clear();

  // ajout des PNJs
  for(int i = 0; i < nombre_pnj; ++i)
  {
    m_listEntite.push_back(std::make_unique<CActor>(false));
    m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, taille_carree_map * 40.f), CRandom::floatInRange(0.f, taille_carree_map * 40.f)));
  }

  // ajout des evenement
  unsigned int indiceDecalage = m_listEntite.size();
  for(unsigned int i = indiceDecalage; i < nombre_evenement + indiceDecalage; ++i)
  {
    m_listEntite.push_back(std::make_unique<CEvent_pub>());
    m_listEntite[i].get()->setPosition(sf::Vector2f(CRandom::floatInRange(0.f, taille_carree_map * 40.f), CRandom::floatInRange(0.f, taille_carree_map * 40.f)));
  }
}

void CServeur::loopGame(void)
{
  while(1)
  {
    connection();

  //  receiveUDP();
    updateGame();
  //  sendUDP();
  }
}

void CServeur::updateGame(void)
{

}
