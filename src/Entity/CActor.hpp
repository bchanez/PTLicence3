#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/CRandom.hpp"

class CActor : public CEntity
{
    struct Key { bool left, right, up, down, shift; };

  public:

    explicit CActor(bool isCharacter);
    virtual ~CActor(void);

    void setTexture(void);
    void setAnimation(void) override;
    void input(sf::Event * event) override;
    void update(float dt) override;

  private:

    bool m_isCharacter;

    Key m_key;
    enum Estate {e_idle, e_walk, e_run, e_action, e_dead, e_wander, e_question, e_disappear};

    enum EAnimation {e_walk_right, e_walk_left};
    unsigned int m_nb_animation = 2;

    sf::Vector2i m_goal_point;
};
