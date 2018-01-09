#pragma once

#include <memory>
#include <vector>
#include <list>
#include <SFML/Network.hpp>
#include "../Tools/DEBUG.hpp"
#include "../Tools/CRandom.hpp"
#include "../Entity/CMap.hpp"
#include "../Entity/CActor.hpp"
#include "../Entity/CEvent_pub.hpp"
#include "CDonnees.hpp"

class CServeur
{
  public:
    explicit CServeur(void);
    virtual ~CServeur(void);

    // TCP
    void connection(void);
    void sendTCP(void);
    void receiveTCP(void);

    // UDP
    void sendUDP(void);
    void receiveUDP(void);

    // methode pour la partie
    void initGame(int taille_carree_map, int nombre_pnj, int nombre_evenement);
    void loopGame(void);
    void updateGame(void);

  private:
    // server
    //tcp
    sf::TcpListener listenerSocket;
    std::list<sf::TcpSocket*> clients;
    sf::SocketSelector selector;

    //udp
    sf::UdpSocket udpSocket;

    struct Client {
      unsigned int indice;
      sf::IpAddress adresse;
      unsigned short port;
    };
    std::vector<Client> m_listClient;

    //donnees
    sf::Packet packet;
    std::vector<struct DonneesInit> m_DonneesInit;
    std::vector<struct Donnees> m_Donnees;

    // variable for game
    CMap m_map;
    std::vector<std::unique_ptr<CEntity>> m_listEntite; // joueur, pnj, evenement

};
