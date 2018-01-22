#pragma once

#include <memory>
#include <vector>
#include <list>
#include <unistd.h>
#include <SFML/Network.hpp>
#include "../Tools/DEBUG.hpp"
#include "../Tools/CRandom.hpp"
#include "../Entity/CMap.hpp"
#include "../Entity/CActor.hpp"
#include "../Entity/CEvent_pub.hpp"
#include "CDonnees.hpp"
#include "../CConfig.hpp"

class CServeur
{
  public:
    explicit CServeur(void);
    virtual ~CServeur(void);

    void connection(void);
    void send(void);
    void receive(void);

    // methode pour la partie
    void initGame(int nombre_pnj, int nombre_evenement);
    void loopServer(void);
    void updateGame(float dt);

  private:

    sf::Clock m_clock;
    float fps_timer;

    //tcp
    sf::TcpListener listenerSocket;
    std::list<sf::TcpSocket*> clients;
    sf::SocketSelector selector;

    //udp
    sf::UdpSocket udpSocket;

    struct Client {
      unsigned int etat;
      sf::TcpSocket *socketTCP;
      unsigned int indice;
      sf::IpAddress adresse;
      unsigned short port;
      std::vector<unsigned int> synchroPosition; //tab pour syncro la position des entites tous les temps de frame
    };
    std::vector<Client> m_listClient;

    //donnees
    std::vector<struct DonneesInit> m_donneesInit; // donnees pour initialiser une partie
    std::vector<struct Donnees> m_everyDonnees; // toutes les donnees de chaque CEntity
    std::vector<struct Donnees> m_donnees; // donnees d'envoie

    //game
    CMap m_map;
    std::vector<std::unique_ptr<CEntity>> m_listEntite; // joueur, pnj, evenement

};
