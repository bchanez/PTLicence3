#include "CClient.hpp"

/*explicit*/ CClient::CClient(void)
: m_tSend(&CClient::send, this), m_tReceive(&CClient::receive, this) //Init des threads du clients
{
  LOG("CClient constructor\n");
  m_UDPserver.bind(55003);

  m_server = IP_SERV;

  m_isConnected = false;
}

/*virtual*/ CClient::~CClient(void)
{
  LOG("CClient destructor\n");
}

void CClient::connection(void)
{
  sf::Socket::Status status = m_TCPserver.connect(m_server, 55001);
  if (status == sf::Socket::Done)
  {
      LOG("connection ok\n");
      m_isConnected = true;
  }
  else
  {
    LOG("connection error\n");
  }
}

bool CClient::getIsConnected(void)
{
  return m_isConnected;
}

void CClient::disconnection(void)
{
  m_isConnected = false;
  m_TCPserver.disconnect();
}

sf::Packet CClient::receiveInitgame(void)
{
  sf::Packet packet;
  if (m_TCPserver.receive(packet) == sf::Socket::Done)
  {
    LOG("reception init game tcp ok\n");
  }
  else
  {
    LOG("reception init game tcp erreur\n");
  }

  return packet;
}

void CClient::sendState(unsigned int state)
{
  sf::Packet packet;
  packet << (sf::Uint16) state; //Envoie Etat par paquet (TCP car important)
  if (m_TCPserver.send(packet) == sf::Socket::Done)
  {
    LOG("envoie etat tcp ok\n");
  }
  else
  {
    LOG("envoie etat tcp error\n");
  }
}

void CClient::send(void)
{
  while(1) //Boucle while car thread
  {
    for (unsigned int i = 0; i < m_listPacketToSend.size(); ++i)
    {
      m_UDPserver.send(m_listPacketToSend[i], m_server, 55002);
      try {
      m_listPacketToSend.erase(m_listPacketToSend.begin() + i);
    }
    catch (std::exception const& e){
      std::cout << "---------- Error in Send Function of Client : " << e.what() << std::endl;
    }
      i--;
    }
  }
}

void CClient::receive(void)
{
  while(1) //same as send
  {
    sf::Packet packet;
    sf::IpAddress server;
    unsigned short port;
    if(m_UDPserver.receive(packet, server, port) == sf::Socket::Done)
    {
      addPacketReceive(packet);
    }
  }
}

void CClient::addPacketToSend(sf::Packet p) //Ajoute le paquet au tableau
{
  m_listPacketToSend.push_back(p);
}

void CClient::addPacketReceive(sf::Packet p) //Idem
{
  m_listPacketReceive.push_back(p);
}

std::vector<sf::Packet> CClient::getListPacketReceive(void) //On renvoit la liste de paquets
{
  return m_listPacketReceive;
}

void CClient::removePacketReceivedFromBeginingToIndex(unsigned int index) // supprime l sous-liste de paquet à partir de l'indice indice
{
  for(unsigned int i = 0; i < index; ++i)
  {
    try {
      m_listPacketReceive.erase(m_listPacketReceive.begin());
    }
    catch (std::exception const& e){
      std::cout << "---------- Error in Client Thread : " << e.what() << std::endl;
    }
  }
}

sf::Thread * CClient::getThreadSend(void) //Thread (CApplication)
{
  return &m_tSend;
}

sf::Thread * CClient::getThreadReceive(void) //Idem
{
  return &m_tReceive;
}
