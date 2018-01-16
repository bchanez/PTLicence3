#pragma once

#include <SFML/Graphics.hpp>
#include "../Tools/CDrawable.hpp"
#include "../Tools/CAnimation.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Server/CDonnees.hpp"

#define WALK_SPEED 60
#define RUN_SPEED 120

class CEntity : public CDrawable
{

  public:
    explicit CEntity(void);
    virtual ~CEntity(void);

    sf::Vector2f getPosition(void);
    void setPosition(sf::Vector2f pos);

    virtual void setAnimation(void) = 0;

    int getState(void);
    void setState(int);

    virtual void update(bool isServer, float dt) = 0;
    virtual void input(void) = 0;

    struct DonneesInit getDonneesInit(void);
    struct Donnees getDonnees(void);
    void setDonnees(struct Donnees d);

  protected:

    struct DonneesInit m_donneesInit;
    struct Donnees m_donnees;

    unsigned int m_move_speed;

    enum Estate {e_idle};
    unsigned int m_state;

    enum Eorientation {e_right, e_left};
    unsigned int m_orientation;

    enum EAnimation {};
    unsigned int m_nb_animation;
    std::vector<CAnimation> m_animation;
};
