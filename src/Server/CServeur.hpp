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
#include <exception>

class CServeur
{
  public:
    explicit CServeur(void);  //Constructeur
    virtual ~CServeur(void);  //Destructeur (avec le ~ devant)

    void connection(void);    //Créer la conneciont (attend un client et s'il est accepté l'ajoute à un tableau de clients)
    void send(void);          //Envoyer des paquets soit en UDP soit en TCP
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
      std::vector<struct Donnees> donnees; // donnees d'envoie
    };
    std::vector<Client> m_listClient;   //Tableau de clients

    //donnees
    std::vector<struct DonneesInit> m_donneesInit; // donnees pour initialiser une partie
    std::vector<struct Donnees> m_everyDonnees; // toutes les donnees de chaque CEntity

    //game
    CMap m_map;
    std::vector<std::unique_ptr<CEntity>> m_listEntite; // joueur, pnj, evenement

};
