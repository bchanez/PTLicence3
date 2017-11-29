#ifndef CMAP_
#define CMAP_

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include <iostream>

class CMap : public CEntity
{

public :

	CMap();

  void getEvent(sf::Event &event);
  void update();

protected :

private :


};

#endif
