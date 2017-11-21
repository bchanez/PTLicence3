#ifndef CCHARACTER_
#define CCHARACTER_

#include "CEntity.hpp"
#include "ResourceManager/CResourceHolder.hpp"
#include <iostream>

class CCharacter : public CEntity{

public :

  CCharacter();

  void getEvent(sf::Event &event);
  void update();

protected :

private :

    enum s {idle, walk};
    enum o {right, left};
    sf::Vector2i m_speed;
    unsigned int m_move_speed, m_orientation;

};



#endif
