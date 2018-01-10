#include "CEntity.hpp"

/*explicit*/ CEntity::CEntity(void)
{
  LOG("CEntity Constructor\n");

  m_key.left = m_key.right = m_key.up = m_key.down = m_key.shift = false;

  m_position = sf::Vector2f(0.f, 0.f);
  m_sprite.setPosition(m_position);

  m_state = e_idle;
  m_orientation = e_right;


  m_donneesInit.classe = "";
  for (unsigned int i = 0; i < 4; ++i)
  {
    m_donneesInit.textures[i] = 0;
    for (unsigned int j = 0; j < 3; ++j)
    {
      m_donneesInit.textures_color[i][j] = 0;
    }
  }
  m_donneesInit.positionX = 0.f; m_donneesInit.positionY = 0.f;
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
  m_donneesInit.positionX = pos.x; m_donneesInit.positionY = pos.y;
}

struct DonneesInit CEntity::getDonneesInit(void)
{
  return m_donneesInit;
}
