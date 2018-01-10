#pragma once

#include <vector>
#include <SFML/Network.hpp>

struct DonneesInit
{
  std::string classe;
  sf:: Uint16 textures[4];
  sf:: Uint16 textures_color[4][3];
  float positionX, positionY;
};

struct Donnees
{
  sf::Int8 indice;
  float positionX, positionY;
  bool keyLeft, keyRight, keyUp, keyDown, keyShift;
};

sf::Packet& operator <<(sf::Packet& packet, const struct DonneesInit& d);
sf::Packet& operator >>(sf::Packet& packet, struct DonneesInit& d);
sf::Packet& operator <<(sf::Packet& packet, const struct Donnees& d);
sf::Packet& operator >>(sf::Packet& packet, struct Donnees& d);
