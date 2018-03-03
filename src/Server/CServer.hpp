#pragma once

#include <memory>
#include <vector>
#include <list>
#include <unistd.h>
#include <SFML/Network.hpp>
#include "../Tools/DEBUG.hpp"
#include "../Tools/CRandom.hpp"
#include "../Tools/CCollision.hpp"
#include "../Entity/CMap.hpp"
#include "../Entity/CActor.hpp"
#include "../Entity/CEvent_pub.hpp"
#include "CData.hpp"
#include "../CConfig.hpp"
#include <exception>

class CServer
{
  public:
    explicit CServer(void);  //Constructeur
    virtual ~CServer(void);  //Destructeur (avec le ~ devant)

    void connection(void);    //Créer la conneciont (attend un client et s'il est accepté l'ajoute à un tableau de clients)
    void send(void);          //Envoyer des paquets soit en UDP soit en TCP
    void receive(void);

    // methode pour la partie
    void initGame(int nb_npc, int nb_event);
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
      unsigned int state;
      sf::TcpSocket *socketTCP;
      unsigned int index;
      sf::IpAddress adress;
      unsigned short port;
      std::vector<unsigned int> synchroPosition; //tab pour syncro la position des entites tous les temps de frame
      std::vector<struct Data> data; // donnees d'envoie
    };
    std::vector<Client> m_listClient;   //Tableau de clients

    //donnees
    std::vector<struct DataInit> m_dataInit; // donnees pour initialiser une partie
    std::vector<struct Data> m_everyData; // toutes les donnees de chaque CEntity

    //game
    CMap m_map;
    std::vector<std::unique_ptr<CEntity>> m_listEntities
    ; // joueur, pnj, evenement

};
