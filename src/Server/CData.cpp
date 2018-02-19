#include "CData.hpp"

sf::Packet& operator <<(sf::Packet& packet, const DataInit& d) //Données dans paquet
{
  packet << d.index << d.state << d.cclass;
  for (int i = 0; i < 4; ++i)
    packet << d.textures[i];
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 3; ++j)
      packet << d.textures_color[i][j];
  packet << d.positionX << d.positionY;

  return packet;
}


sf::Packet& operator >>(sf::Packet& packet, DataInit& d) //Paquet dans données
{
  packet >> d.index >> d.state >> d.cclass;
  for (int i = 0; i < 4; ++i)
    packet >> d.textures[i];
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 3; ++j)
      packet >> d.textures_color[i][j];
  packet >> d.positionX >> d.positionY;

  return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const Data& d) //idem
{
    return packet <<
      d.index <<
      d.state <<
      d.mustUpdatePosition <<
      d.positionX << d.positionY <<
      d.keyLeft << d.keyRight << d.keyUp << d.keyDown << d.keyShift << d.mouseLeft;
}

sf::Packet& operator >>(sf::Packet& packet, Data& d)
{
  return packet >>
    d.index >>
    d.state >>
    d.mustUpdatePosition >>
    d.positionX >> d.positionY >>
    d.keyLeft >> d.keyRight >> d.keyUp >> d.keyDown >> d.keyShift >> d.mouseLeft;
}

bool operator != (const struct Data& d1, const struct Data& d2)
{
  return d1.state != d2.state
    || d1.keyLeft != d2.keyLeft
    || d1.keyRight != d2.keyRight
    || d1.keyUp != d2.keyUp
    || d1.keyDown != d2.keyDown
    || d1.keyShift != d2.keyShift
    || d1.mouseLeft != d2.mouseLeft
  ;
}
