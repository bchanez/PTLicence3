#ifndef CENTITY_HPP_
#define CENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "CDrawable.hpp"
#include "../Tools/CAnimation.hpp"
#include "../Tools/DEBUG.hpp"

#define WALK_SPEED 60
#define RUN_SPEED 120

class CEntity : public CDrawable
{

  public:
    explicit CEntity(void);
    virtual ~CEntity(void);

    virtual void update(float dt);

  protected:

    sf::Vector2f m_position;
    unsigned int m_move_speed;

    enum Estate {};
    unsigned int m_state;

    enum Eorientation {e_right, e_left};
    unsigned int m_orientation;

    enum EAnimation {};
    unsigned int m_nb_animation;
    std::vector<CAnimation> m_animation;
};

#endif
