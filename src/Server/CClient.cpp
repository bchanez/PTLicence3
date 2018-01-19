#include "CClient.hpp"

/*explicit*/ CClient::CClient(void)

{
  LOG("CClient constructor");
  m_UDPserver.bind(55003);
  m_UDPserver.setBlocking(false);

  //m_serveur = "192.168.43.26";
  m_serveur = "localhost";
}

/*virtual*/ CClient::~CClient(void)
{
  LOG("CClient destructor");
}

void CClient::connexion(void)
{
  sf::Socket::Status status = m_TCPserver.connect(m_serveur, 55001);
  if (status == sf::Socket::Done)
  {
      LOG("connexion ok\n");
  }
  else
  {
    LOG("connexion erreur\n");
  }
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
  packet << (sf::Uint16) state;
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
  for (unsigned int i = 0; i < m_listPacketToSend.size(); ++i)
  {
    m_UDPserver.send(m_listPacketToSend[i], m_serveur, 55002);
    m_listPacketToSend.erase(m_listPacketToSend.begin() + i);
    i--;
  }
}

void CClient::receive(void)
{
  sf::Packet packet;
  sf::IpAddress serveur;
  unsigned short port;
  if(m_UDPserver.receive(packet, serveur, port) == sf::Socket::Done)
  {
    addPacketReceive(packet);
  }
}

void CClient::addPacketToSend(sf::Packet p)
{
  m_listPacketToSend.push_back(p);
}

void CClient::addPacketReceive(sf::Packet p)
{
  m_listPacketReceive.push_back(p);
}

std::vector<sf::Packet> CClient::getListPacketReceive(void)
{
  return m_listPacketReceive;
}

void CClient::removePacketReceivedFromBeginingToIndice(unsigned int indice)
{
  for(unsigned int i = 0; i < indice; ++i)
  {
    m_listPacketReceive.erase(m_listPacketReceive.begin() + i);
  }
}
