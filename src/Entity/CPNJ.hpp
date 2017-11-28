#ifndef CPNJ_HPP_
#define CPNJ_HPP_

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include <iostream>

class CPNJ : public CEntity
{
  public:

    explicit CPNJ();
    virtual ~CPNJ();

    void setTexture(void);
    void setAnimation(void);
    void update(float dt);

  private:

    enum state {e_idle, e_walk, e_run, e_action, e_wander, e_question, e_dead, e_disappear};

    int m_nb_animation = 2;
    enum EAnimation {e_walk_right, e_walk_left};
};

#endif
