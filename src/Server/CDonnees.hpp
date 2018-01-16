#pragma once

#include <vector>
#include <SFML/Network.hpp>

struct DonneesInit
{
  sf::Uint16 indice;
  std::string classe;
  sf:: Uint16 textures[4];
  sf:: Uint16 textures_color[4][3];
  float positionX, positionY;
};

struct Donnees
{
  sf::Uint16 indice;
  float positionX, positionY;
  bool keyLeft, keyRight, keyUp, keyDown, keyShift;
};

sf::Packet& operator <<(sf::Packet& packet, const struct DonneesInit& d);
sf::Packet& operator >>(sf::Packet& packet, struct DonneesInit& d);
sf::Packet& operator <<(sf::Packet& packet, const struct Donnees& d);
sf::Packet& operator >>(sf::Packet& packet, struct Donnees& d);
bool operator != (const struct Donnees& d1, const struct Donnees& d2);
