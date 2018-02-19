#pragma once

#include <vector>
#include <SFML/Network.hpp>

//Uint16 unsigned int sur 16bits (utilisé pour problèmes d'architecture)

struct DataInit
{
  sf::Uint16 index;  //Indice de position de l'Entité
  sf::Uint16 state;   //Etat du Client
  std::string cclass; //CActor ou CEvent
  sf:: Uint16 textures[4];    //Textures
  sf:: Uint16 textures_color[4][3]; //Textures
  float positionX, positionY;   //Position X Y Des différentes entités
};

struct Data
{
  sf::Uint16 index;
  sf::Uint16 state;
  bool mustUpdatePosition; //Temps de refresh
  float positionX, positionY; //Position
  bool keyLeft, keyRight, keyUp, keyDown, keyShift, mouseLeft; //Touches
};

//Surcharger l'opérateur,
sf::Packet& operator <<(sf::Packet& packet, const struct DataInit& d);
sf::Packet& operator >>(sf::Packet& packet, struct DataInit& d);
sf::Packet& operator <<(sf::Packet& packet, const struct Data& d);
sf::Packet& operator >>(sf::Packet& packet, struct Data& d);
bool operator != (const struct Data& d1, const struct Data& d2);
