#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/CRandom.hpp"
#include "CWeapon.hpp"
#include <vector>

class CActor : public CEntity
{
  public:

    explicit CActor(void);
    explicit CActor(struct DonneesInit donnees);
    virtual ~CActor(void);

    void setTexture(void);
    void setTexture(struct DonneesInit donnees);

    void setAnimation(void) override;
    void input(void);
    void update(float dt) override;
    void serverUpdate(float dt) override;

    void setIsCharacter(bool isCharacter);

  private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
        if (m_attack)
          target.draw(m_knife);
    }

    bool m_isCharacter;
    bool m_slow;

    enum Estate {e_idle, e_walk, e_run, e_action, e_attack, e_dead, e_wander, e_question, e_disappear};

    enum EAnimation {e_walk_right, e_walk_left};
    unsigned int m_nb_animation = 2;

    float m_timer;

    CWeapon m_knife;
    bool m_attack;

    sf::Vector2f m_stop;
    sf::Vector2i m_goal_point;
};
