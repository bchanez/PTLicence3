#include "CEntity.hpp"

/*explicit*/ CEntity::CEntity(void)
{
  LOG("CEntity Constructor\n");
}

/*virtual*/ CEntity::~CEntity(void)
{
  LOG("CEntity Destructor\n");
}

/*virtual*/ void CEntity::update(float dt) {}

sf::Vector2f CEntity::getPosition(void)
{
  return m_position;
}

void CEntity::setPosition(sf::Vector2f pos)
{
  m_position = pos;
  m_sprite.setPosition(m_position);
}
