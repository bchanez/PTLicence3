#pragma once

#include <vector>
#include <SFML/Network.hpp>

//Uint16 unsigned int sur 16bits (utilisé pour problèmes d'architecture)

struct DonneesInit
{
  sf::Uint16 indice;  //Indice de position de l'Entité
  sf::Uint16 state;   //Etat du Client
  std::string classe; //CActor ou CEvent
  sf:: Uint16 textures[4];    //Textures
  sf:: Uint16 textures_color[4][3]; //Textures
  float positionX, positionY;   //Position X Y Des différentes entités
};

struct Donnees
{
  sf::Uint16 indice;
  sf::Uint16 state;
  bool mustUpdatePosition; //Temps de refresh
  float positionX, positionY; //Position
  bool keyLeft, keyRight, keyUp, keyDown, keyShift, mouseLeft; //Touches
};

//Surcharger l'opérateur, 
sf::Packet& operator <<(sf::Packet& packet, const struct DonneesInit& d);
sf::Packet& operator >>(sf::Packet& packet, struct DonneesInit& d);
sf::Packet& operator <<(sf::Packet& packet, const struct Donnees& d);
sf::Packet& operator >>(sf::Packet& packet, struct Donnees& d);
bool operator != (const struct Donnees& d1, const struct Donnees& d2);
