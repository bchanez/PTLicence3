#include "CEntity.hpp"

/*explicit*/ CEntity::CEntity(void)
{
  LOG("CEntity Constructor\n");

  m_key.left = m_key.right = m_key.up = m_key.down = m_key.shift = false;

  m_position = sf::Vector2f(0.f, 0.f);
  m_sprite.setPosition(m_position);

  m_state = e_idle;
  m_orientation = e_right;
}

/*virtual*/ CEntity::~CEntity(void)
{
  LOG("CEntity Destructor\n");
}

sf::Vector2f CEntity::getPosition(void)
{
  return m_position;
}

void CEntity::setPosition(sf::Vector2f pos)
{
  m_position = pos;
  m_sprite.setPosition(m_position);
}
