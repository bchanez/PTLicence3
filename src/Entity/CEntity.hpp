#ifndef CENTITY_HPP_
#define CENTITY_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class CEntity : public sf::Drawable
{

  public:
    CEntity();
    ~CEntity();
    void update();

  protected:

    sf::Sprite m_sprite;
    sf::RenderTexture m_prerender;

    sf::Vector2i m_position;
    unsigned int m_move_speed, m_orientation;
    enum orientation {right, left};

    unsigned int m_state;

  private:

    //Fonction pour afficher le sprite
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite);
    }
};

#endif
