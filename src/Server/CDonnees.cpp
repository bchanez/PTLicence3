#include "CDonnees.hpp"

sf::Packet& operator <<(sf::Packet& packet, const DonneesInit& d)
{
  packet << d.classe;
  for (int i = 0; i < 4; ++i)
    packet << d.textures[i];
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 3; ++j)
      packet << d.textures_color[i][j];
  packet << d.positionX << d.positionY;

  return packet;
}


sf::Packet& operator >>(sf::Packet& packet, DonneesInit& d)
{
  packet >> d.classe;
  for (int i = 0; i < 4; ++i)
    packet >> d.textures[i];
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 3; ++j)
      packet >> d.textures_color[i][j];
  packet >> d.positionX >> d.positionY;

  return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const Donnees& d)
{
    return packet <<
      d.indice <<
      d.positionX << d.positionY <<
      d.keyLeft << d.keyRight << d.keyUp << d.keyDown << d.keyShift;
}

sf::Packet& operator >>(sf::Packet& packet, Donnees& d)
{
  return packet >>
    d.indice >>
    d.positionX >> d.positionY >>
    d.keyLeft >> d.keyRight >> d.keyUp >> d.keyDown >> d.keyShift;
}
