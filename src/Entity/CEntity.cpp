#include "CEntity.hpp"

/*explicit*/ CEntity::CEntity(void)
{
  LOG("CEntity Constructor\n");

  m_dataInit.cclass = "";
  for (unsigned int i = 0; i < 4; ++i)
  {
    m_dataInit.textures[i] = 0;
    for (unsigned int j = 0; j < 3; ++j)
    {
      m_dataInit.textures_color[i][j] = 0;
    }
  }
  m_dataInit.positionX = m_dataInit.positionY = 0.f;


  m_data.index = 0;
  m_data.state = 0;
  m_data.mustUpdatePosition = false;
  m_data.positionX = m_data.positionY = 0.f;
  m_data.keyLeft = m_data.keyRight = m_data.keyUp = m_data.keyDown = m_data.keyShift = m_data.mouseLeft = false;

  m_isAlive = true;

  m_sprite.setPosition(sf::Vector2f(m_data.positionX, m_data.positionY));

  m_data.state = e_idle;
  m_orientation = e_right;
}

/*virtual*/ CEntity::~CEntity(void)
{
  LOG("CEntity Destructor\n");
}

sf::Vector2f CEntity::getPosition(void)
{
  return sf::Vector2f(m_data.positionX, m_data.positionY);
}

void CEntity::setPosition(sf::Vector2f pos)
{
  m_dataInit.positionX = pos.x; m_dataInit.positionY = pos.y;
  m_data.positionX = pos.x; m_data.positionY = pos.y;
  m_sprite.setPosition(sf::Vector2f(m_data.positionX, m_data.positionY));
}

struct DataInit CEntity::getDataInit(void)
{
  return m_dataInit;
}

struct Data CEntity::getData(void)
{
  return m_data;
}

void CEntity::setData(struct Data d)
{
    m_data.state = d.state;

    m_data.keyLeft = d.keyLeft;
    m_data.keyRight = d.keyRight;
    m_data.keyUp = d.keyUp;
    m_data.keyDown = d.keyDown;
    m_data.keyShift = d.keyShift;
    m_data.mouseLeft = d.mouseLeft;

    if(d.mustUpdatePosition)
    {
        m_data.positionX = d.positionX;
        m_data.positionY = d.positionY;
    }
}

bool CEntity::getIsAlive(void)
{
  return m_isAlive;
}

void CEntity::setIsAlive(bool isAlive)
{
  m_isAlive = isAlive;
}
