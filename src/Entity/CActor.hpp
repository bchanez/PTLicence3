#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CDisplay.hpp"
#include "CWeapon.hpp"
//#include "CObject.hpp"

class CActor : public CEntity
{
  public:

    explicit CActor(unsigned int index, std::vector<std::unique_ptr<CEntity>> * listEntities);
    explicit CActor(struct DataInit data);
    virtual ~CActor(void);

    void setTexture(void);
    void setTexture(struct DataInit data);

    void setAnimation(void) override;
    void input(void) override;
    void update(bool isServer, float dt) override;

    void setIsCharacter(bool isCharacter);
    bool getMustDisappear(void);

    void setGoalPoint(sf::Vector2i dot);
    sf::Vector2i getGoalPoint(void);

    void setEvent(bool event);
    bool getEvent(void);

  private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
        if (m_attack)
          target.draw(m_knife);
    }

    bool m_isCharacter;

    enum Estate {e_idle, e_walk, e_run, e_action, e_attack, e_slow, e_dead, e_wander, e_question, e_disappear};

    enum EAnimation {e_walk_right, e_walk_left};
    unsigned int m_nb_animation = 2;

    float m_timer;

    CWeapon m_knife;
    bool m_attack;
    bool m_mustDisappear;

    sf::Vector2f m_stop;
    sf::Vector2i m_goal_point;

    bool m_event;
    float m_fly;
};
