#include "CDonnees.hpp"

sf::Packet& operator <<(sf::Packet& packet, const DonneesInit& d)
{
  packet << d.indice << d.state << d.classe;
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
  packet >> d.indice >> d.state >> d.classe;
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
      d.state <<
      //d.positionX << d.positionY <<
      d.keyLeft << d.keyRight << d.keyUp << d.keyDown << d.keyShift << d.mouseLeft;
}

sf::Packet& operator >>(sf::Packet& packet, Donnees& d)
{
  return packet >>
    d.indice >>
    d.state >>
    //d.positionX >> d.positionY >>
    d.keyLeft >> d.keyRight >> d.keyUp >> d.keyDown >> d.keyShift >> d.mouseLeft;
}

bool operator != (const struct Donnees& d1, const struct Donnees& d2)
{
  return d1.keyLeft != d2.keyLeft
    || d1.keyRight != d2.keyRight
    || d1.keyUp != d2.keyUp
    || d1.keyDown != d2.keyDown
    || d1.keyShift != d2.keyShift
    || d1.mouseLeft != d2.mouseLeft
  ;
}
