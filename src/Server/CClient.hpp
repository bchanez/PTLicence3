#pragma once

#include <memory>
#include <vector>
#include <list>
#include <unistd.h>
#include <SFML/Network.hpp>
#include "../Tools/DEBUG.hpp"
#include "CData.hpp"
#include "../CConfig.hpp"
#include <exception>

class CClient
{
  public:
    explicit CClient(void);
    virtual ~CClient(void);

    void connection(void);
    void disconnection(void);

    sf::Packet receiveInitgame(void); //Reçoie les paquets
    void sendState(unsigned int state);

    void send(void);
    void receive(void);

    void addPacketToSend(sf::Packet p);
    void addPacketReceive(sf::Packet p);

    std::vector<sf::Packet> getListPacketReceive(void);
    void removePacketReceivedFromBeginingToIndex(unsigned int index);

    sf::Thread * getThreadSend(void);
    sf::Thread * getThreadReceive(void);

  private:
    sf::IpAddress m_server;

    sf::TcpSocket m_TCPserver;
    sf::UdpSocket m_UDPserver;

    std::vector<sf::Packet> m_listPacketToSend;   //Liste de paquets
    std::vector<sf::Packet> m_listPacketReceive;  //Liste de paquets

    sf::Thread m_tSend;
    sf::Thread m_tReceive;
};
