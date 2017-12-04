#include "CEvent_pub.hpp"

/*explicit*/ CEvent_pub::CEvent_pub(void)
{
  LOG("CEvent_pub Constructor\n");

  m_position = sf::Vector2f(960.f, 540.f);
  m_sprite.setPosition(m_position);
  m_sprite.setOrigin(sf::Vector2f(20, 30));

  m_state = e_idle;

  setTexture();
  setAnimation();
}

/*virtual*/ CEvent_pub::~CEvent_pub(void)
{
  LOG("CEvent_pub Destructor\n");
}

// donne la texture a l'evenemnt
void CEvent_pub::setTexture(void)
{
  m_sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Pub));
}

// definie les animations de l'evenement
void CEvent_pub::setAnimation(void)
{
  for (unsigned int i = 0; i < m_nb_animation ; ++i)
    m_animation.push_back(CAnimation());

  for (int i = 0; i < 36 ; ++i)
  {
    m_animation[e_idle].addFrame(sf::IntRect(i * 100, 0, 100, 80), 0.1f);
    m_animation[e_call].addFrame(sf::IntRect(i * 100, 80, 100, 80), 0.1f);
    m_animation[e_active].addFrame(sf::IntRect(i * 100, 160, 100, 80), 0.1f);
  }
}

void CEvent_pub::update(float dt)
{
  switch (m_state)
  {
    case e_idle :
    {
      m_sprite.setTextureRect(m_animation[e_idle].getCurrentFrame());
    }
    break;

    case e_call :
    {
      m_sprite.setTextureRect(m_animation[e_call].getCurrentFrame());
    }
    break;

    case e_active :
    {
      m_sprite.setTextureRect(m_animation[e_active].getCurrentFrame());
    }
    break;

    default : {} break;
  }
}
