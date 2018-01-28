#pragma once

#include "CEntity.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CDisplay.hpp"
#include "../Tools/CRandom.hpp"
#include "../Tools/CCollision.hpp"
#include "CWeapon.hpp"
#include <vector>

class CActor : public CEntity
{
  public:

    explicit CActor(unsigned int indice, std::vector<std::unique_ptr<CEntity>> * listEntite);
    explicit CActor(struct DonneesInit donnees);
    virtual ~CActor(void);

    void setTexture(void);
    void setTexture(struct DonneesInit donnees);

    void setAnimation(void) override;
    void input(void) override;
    void update(bool isServer, float dt) override;

    void setIsCharacter(bool isCharacter);
    bool getMustDisappear(void);

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

    std::vector<std::unique_ptr<CEntity>> * m_listEntite; //Le joueur a accès à chaque entité
};
