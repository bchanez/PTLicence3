#include "CDonnees.hpp"

sf::Packet& operator <<(sf::Packet& packet, const DonneesInit& d)
{
    return packet <<
      d.classe <<
      d.textureCheveux << d.textureCorps << d.textureTeeShirt << d.texturePantalon <<
      d.couleurCheveuxR << d.couleurCheveuxG << d.couleurCheveuxB <<
      d.couleurCorpsR << d.couleurCorpsG << d.couleurCorpsB <<
      d.couleurTeeShirtR << d.couleurTeeShirtG << d.couleurTeeShirtB <<
      d.couleurPantalonR << d.couleurPantalonG << d.couleurPantalonB <<
      d.positionX << d.positionY;
}


sf::Packet& operator >>(sf::Packet& packet, DonneesInit& d)
{
  return packet >>
    d.classe >>
    d.textureCheveux >> d.textureCorps >> d.textureTeeShirt >> d.texturePantalon >>
    d.couleurCheveuxR >> d.couleurCheveuxG >> d.couleurCheveuxB >>
    d.couleurCorpsR >> d.couleurCorpsG >> d.couleurCorpsB >>
    d.couleurTeeShirtR >> d.couleurTeeShirtG >> d.couleurTeeShirtB >>
    d.couleurPantalonR >> d.couleurPantalonG >> d.couleurPantalonB >>
    d.positionX >> d.positionY;
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
