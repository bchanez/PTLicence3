#include "CClient.hpp"

/*explicit*/ CClient::CClient(void)
: m_tSend(&CClient::send, this), m_tReceive(&CClient::receive, this) //Init des threads du clients
{
  LOG("CClient constructor\n");
  m_UDPserver.bind(55003);

  m_serveur = IP_SERV;
}

/*virtual*/ CClient::~CClient(void)
{
  LOG("CClient destructor\n");
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

void CClient::deconnexion(void)
{
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
      m_UDPserver.send(m_listPacketToSend[i], m_serveur, 55002);
      m_listPacketToSend.erase(m_listPacketToSend.begin() + i);
      i--;
    }
  }
}

void CClient::receive(void)
{
  while(1) //Pareil que send
  {
    sf::Packet packet;
    sf::IpAddress serveur;
    unsigned short port;
    if(m_UDPserver.receive(packet, serveur, port) == sf::Socket::Done)
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

void CClient::removePacketReceivedFromBeginingToIndice(unsigned int indice) // supprime l sous-liste de paquet à partir de l'indice indice
{
  for(unsigned int i = 0; i < indice; ++i)
  {
    m_listPacketReceive.erase(m_listPacketReceive.begin());
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
