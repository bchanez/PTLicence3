#include "CEvent_feu.hpp"

/*explicit*/ CEvent_feu::CEvent_feu(void)
{
  LOG("CEvent_feu Constructor\n");
}

/*virtual*/ CEvent_feu::~CEvent_feu(void)
{
  LOG("CEvent_feu Destructor\n");
}

// donne la texture a l'evenemnt
void CEvent_feu::setTexture(void)
{

}

// definie les animations de l'evenement
void CEvent_feu::setAnimation(void)
{

}

void CEvent_feu::input(bool left, bool right, bool up, bool down, bool shift)
{
  m_key.left = left; m_key.right = right; m_key.up = up ; m_key.down = down; m_key.shift = shift;
}

void CEvent_feu::update(float dt)
{
  (void)dt;
}
