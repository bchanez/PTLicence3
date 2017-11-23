#ifndef CENTITY_
#define CENTITY_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class CEntity : public sf::Drawable
{

public :

  CEntity();

  void update();

protected :

  sf::Sprite m_sprite;
  sf::RenderTexture m_prerender;
  unsigned int m_state;

  sf::Clock m_clock, m_move_clock;


private :

  //Fonction pour afficher le sprite
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
      target.draw(m_sprite);
  }


};

#endif
