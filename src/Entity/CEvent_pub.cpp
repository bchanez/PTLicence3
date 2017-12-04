#include "CEvent_pub.hpp"

/*explicit*/ CEvent_pub::CEvent_pub(void)
{
  LOG("CEvent_pub Constructor\n");
}

/*virtual*/ CEvent_pub::~CEvent_pub(void)
{
  LOG("CEvent_pub Destructor\n");


  setTexture();
  setAnimation();
}

// donne la texture a l'evenemnt
void CEvent_pub::setTexture(void)
{
  m_sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));
}

// definie les animations de l'evenement
void CEvent_pub::setAnimation(void)
{
  for (unsigned int i = 0; i < m_nb_animation ; ++i)
    m_animation.push_back(CAnimation());

  for (int i = 0; i < 4 ; ++i)
  {
    m_animation[e_walk_right].addFrame(sf::IntRect(i * 40, 0, 40, 40), 0.1f);
    m_animation[e_walk_left].addFrame(sf::IntRect(i * 40, 40, 40, 40), 0.1f);
  }
}

void CEvent_pub::update(float dt)
{
  switch (m_state)
  {
    case e_idle :
    {
      m_animation[e_walk_left].restart();
      m_sprite.setTextureRect(m_animation[e_walk_left].getCurrentFrame());

      break;
    }
    case e_call :
    {

      break;
    }
    case e_active :
    {

      break;
    }
    default : { break; }
}
