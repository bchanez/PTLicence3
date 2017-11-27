#include "CCharacter.hpp"
#include "../Tools/DEBUG.hpp"

CCharacter::CCharacter()
{
  LOG("CCharacter Constructor\n");

  m_position = sf::Vector2i(0, 0);
  m_move_speed = 1;
}

CCharacter::~CCharacter()
{
  LOG("CCharacter Destructor\n");
}

CInput& CCharacter::getInput()
{
  return m_input;
}

void CCharacter::getEvent(float dt)
{
  if(m_input.getButton().left)
  {
    m_position.x += -m_move_speed;
  }
  if(m_input.getButton().right)
  {
    m_position.x += m_move_speed;
  }
  if(m_input.getButton().up)
  {
    m_position.y += -m_move_speed;
  }
  if(m_input.getButton().down)
  {
    m_position.y += m_move_speed;
  }
  if(m_input.getButton().shift)
  {

  }
}


void CCharacter::update(float dt)
{
  getEvent(dt);

  switch (m_state)
  {
    case idle :
      break;

    case walk :
      break;

    case run :
      break;

    case action :
      break;

    case dead :
      break;

    case disappear :
      break;

    default :
      break;
  }
}
