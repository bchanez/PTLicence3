#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CRandom.hpp"

class CPNJ : public CEntity
{
  public:

    explicit CPNJ();
    virtual ~CPNJ();

    void setTexture(void);
    void setAnimation(void);
    void update(float dt);

  private:

    enum state {e_idle, e_walk, e_action, e_run, e_wander, e_question, e_dead, e_disappear};

    enum EAnimation {e_walk_right, e_walk_left};
    unsigned int m_nb_animation = 2;

    sf::Vector2i m_goal_point;
};
