#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/CRandom.hpp"

class CActor : public CEntity
{
  public:

    explicit CActor(bool isCharacter);
    explicit CActor(struct DonneesInit donnees);
    virtual ~CActor(void);

    void setTexture(void);
    void setAnimation(void) override;
    void input(bool left, bool right, bool up, bool down, bool shift);
    void update(float dt) override;

    void setIsCharacter(bool isCharacter);

  private:

    bool m_isCharacter;

    enum Estate {e_idle, e_walk, e_run, e_action, e_dead, e_wander, e_question, e_disappear};

    enum EAnimation {e_walk_right, e_walk_left};
    unsigned int m_nb_animation = 2;

    sf::Vector2f m_stop;
    sf::Vector2i m_goal_point;
};
