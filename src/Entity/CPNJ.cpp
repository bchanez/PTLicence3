#include "CPNJ.hpp"
#include "../Tools/DEBUG.hpp"

/*explicit*/ CPNJ::CPNJ()
{
  LOG("CPNJ Constructor\n");

  m_position = sf::Vector2f(960.f, 540.f);
  m_sprite.setPosition(m_position);
  m_sprite.setOrigin(sf::Vector2f(20, 30));

  m_state = e_idle;
  m_orientation = e_right;

  setTexture();
  setAnimation();
}

/*virtual*/ CPNJ::~CPNJ()
{
  LOG("CPNJ Destructor\n");
}

// donne la texture au pnj
void CPNJ::setTexture(void)
{
  m_prerender.create(160, 80);

  m_prerender.clear(sf::Color::Transparent);

  sf::Sprite spr;
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));
  m_prerender.draw(spr);
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Hair_5));
  m_prerender.draw(spr);

  m_prerender.display();


  m_sprite.setTexture(m_prerender.getTexture());
}

// definie les animations du pnj
void CPNJ::setAnimation(void)
{
  for (int i = 0; i < m_nb_animation ; ++i)
    m_animation.push_back(CAnimation());

  for (int i = 0; i < 4 ; ++i)
  {
    m_animation[e_walk_right].addFrame(sf::IntRect(i * 40, 0, 40, 40), 0.1f);
    m_animation[e_walk_left].addFrame(sf::IntRect(i * 40, 40, 40, 40), 0.1f);
  }
}

void CPNJ::update(float dt)
{
  switch (m_state)
  {
    case e_idle :
    {

    }
    break;

    case e_walk :
    {

    }
    break;

    case e_run :
    {

    }
    break;

    case e_action :
    {

    }
    break;

    case e_wander :
    {

    }
    break;

    case e_question :
    {

    }
    break;

    case e_dead :
    {

    }
    break;

    case e_disappear :
    {

    }
    break;

    default : {} break;
  }
}
