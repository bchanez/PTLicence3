#pragma once

#include <memory>
#include <vector>
#include <list>
#include <unistd.h>
#include <SFML/Network.hpp>
#include "../Tools/DEBUG.hpp"
#include "CDonnees.hpp"

class CClient
{
  public:
    explicit CClient(void);
    virtual ~CClient(void);

    void connexion(void);
    void deconnexion(void);

    sf::Packet receiveInitgame(void);
    void sendState(unsigned int state);

    void send(void);
    void receive(void);

    void addPacketToSend(sf::Packet p);
    void addPacketReceive(sf::Packet p);

    std::vector<sf::Packet> getListPacketReceive(void);
    void removePacketReceivedFromBeginingToIndice(unsigned int indice);

    sf::Thread * getThreadSend(void);
    sf::Thread * getThreadReceive(void);

  private:
    sf::IpAddress m_serveur;

    sf::TcpSocket m_TCPserver;
    sf::UdpSocket m_UDPserver;

    std::vector<sf::Packet> m_listPacketToSend;
    std::vector<sf::Packet> m_listPacketReceive;

    sf::Thread m_tSend;
    sf::Thread m_tReceive;
};
