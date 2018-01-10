#pragma once

#include <vector>
#include <SFML/Network.hpp>

struct DonneesInit
{
  std::string classe;
  sf::Int8 textureCheveux, textureCorps, textureTeeShirt, texturePantalon;
  sf::Int8 couleurCheveuxR, couleurCheveuxG, couleurCheveuxB,
          couleurCorpsR, couleurCorpsG, couleurCorpsB,
          couleurTeeShirtR, couleurTeeShirtG, couleurTeeShirtB,
          couleurPantalonR, couleurPantalonG, couleurPantalonB;
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
