#ifndef CDRAWABLE_HPP_
#define CDRAWABLE_HPP_

#include <SFML/Graphics.hpp>
#include "../Tools/DEBUG.hpp"


class CDrawable : public sf::Drawable
{

  public:
    explicit CDrawable(void);
    virtual ~CDrawable(void);

    virtual void setTexture(void);

  protected:

    sf::Sprite m_sprite;
    sf::RenderTexture m_prerender;

    //Fonction pour afficher les sprites herite
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }
};

#endif