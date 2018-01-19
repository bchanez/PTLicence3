#include "CEntity.hpp"

/*explicit*/ CEntity::CEntity(void)
{
  LOG("CEntity Constructor\n");

  m_donneesInit.classe = "";
  for (unsigned int i = 0; i < 4; ++i)
  {
    m_donneesInit.textures[i] = 0;
    for (unsigned int j = 0; j < 3; ++j)
    {
      m_donneesInit.textures_color[i][j] = 0;
    }
  }
  m_donneesInit.positionX = m_donneesInit.positionY = 0.f;


  m_donnees.indice = 0;
  m_donnees.state = 0;
  m_donnees.mustUpdatePosition = false;
  m_donnees.positionX = m_donnees.positionY = 0.f;
  m_donnees.keyLeft = m_donnees.keyRight = m_donnees.keyUp = m_donnees.keyDown = m_donnees.keyShift = m_donnees.mouseLeft = false;

  m_sprite.setPosition(sf::Vector2f(m_donnees.positionX, m_donnees.positionY));

  m_state = e_idle;
  m_orientation = e_right;
}

/*virtual*/ CEntity::~CEntity(void)
{
  LOG("CEntity Destructor\n");
}

sf::Vector2f CEntity::getPosition(void)
{
  return sf::Vector2f(m_donnees.positionX, m_donnees.positionY);
}

void CEntity::setPosition(sf::Vector2f pos)
{
  m_donneesInit.positionX = pos.x; m_donneesInit.positionY = pos.y;
  m_donnees.positionX = pos.x; m_donnees.positionY = pos.y;
  m_sprite.setPosition(sf::Vector2f(m_donnees.positionX, m_donnees.positionY));
}

struct DonneesInit CEntity::getDonneesInit(void)
{
  return m_donneesInit;
}

struct Donnees CEntity::getDonnees(void)
{
  return m_donnees;
}

void CEntity::setDonnees(struct Donnees d)
{
  m_donnees.state = d.state;

  m_donnees.keyLeft = d.keyLeft;
  m_donnees.keyRight = d.keyRight;
  m_donnees.keyUp = d.keyUp;
  m_donnees.keyDown = d.keyDown;
  m_donnees.keyShift = d.keyShift;
  m_donnees.mouseLeft = d.mouseLeft;

  if(d.mustUpdatePosition)
  {
      m_donnees.positionX = d.positionX;
      m_donnees.positionY = d.positionY;
  }
}
