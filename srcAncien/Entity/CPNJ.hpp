#ifndef CPNJ_
#define CPNJ_

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include <iostream>
#include <time.h>

class CPNJ : public CEntity
{

  public :

    CPNJ();


    void update();

  protected :

  private :

      void IA();


      enum s {idle, walk, run};
      enum o {right, left};
      sf::Vector2f m_speed;
      sf::Vector2i m_goal_point;
      unsigned int m_move_speed, m_orientation;
      bool m_shift;

};

#endif
