#include "CEntity.hpp"

/*explicit*/ CEntity::CEntity(void)
{
  LOG("CEntity Constructor\n");

  m_position = sf::Vector2f(0.f, 0.f);
  m_sprite.setPosition(m_position);
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
