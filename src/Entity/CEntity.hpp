#ifndef CENTITY_HPP_
#define CENTITY_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#define WALK_SPEED 60
#define RUN_SPEED 120

class CEntity : public sf::Drawable
{

  public:
    explicit CEntity(void);
    virtual ~CEntity(void);

    virtual void setTexture(void);
    virtual void update(float dt);

  protected:

    sf::Sprite m_sprite;
    sf::RenderTexture m_prerender;

    sf::Vector2f m_position;
    unsigned int m_move_speed;

    enum Estate {};
    unsigned int m_state;

    enum Eorientation {e_right, e_left};
    unsigned int m_orientation;

  private:

    //Fonction pour afficher le sprite
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }
};

#endif
