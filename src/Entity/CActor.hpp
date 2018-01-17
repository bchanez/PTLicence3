#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/CRandom.hpp"
#include <vector>

class CActor : public CEntity
{
  public:

    explicit CActor(unsigned int indice);
    explicit CActor(struct DonneesInit donnees);
    virtual ~CActor(void);

    void setTexture(void);
    void setTexture(struct DonneesInit donnees);

    void setAnimation(void) override;
    void input(void);
    void update(bool isServer, float dt) override;

    void setIsCharacter(bool isCharacter);

  private:

    bool m_isCharacter;

    enum Estate {e_idle, e_walk, e_run, e_action, e_attack, e_dead, e_wander, e_question, e_disappear};

    enum EAnimation {e_walk_right, e_walk_left};
    unsigned int m_nb_animation = 2;

    float m_timer;

    sf::Vector2f m_stop;
    sf::Vector2i m_goal_point;
};
