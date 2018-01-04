#include "CEvent_tir.hpp"

/*explicit*/ CEvent_tir::CEvent_tir(void)
{
  LOG("CEvent_tir Constructor\n");
}

/*virtual*/ CEvent_tir::~CEvent_tir(void)
{
  LOG("CEvent_tir Destructor\n");
}

// donne la texture a l'evenemnt
void CEvent_tir::setTexture(void)
{

}

// definie les animations de l'evenement
void CEvent_tir::setAnimation(void)
{

}

void CEvent_tir::input(bool left, bool right, bool up, bool down, bool shift)
{
  m_key.left = left; m_key.right = right; m_key.up = up ; m_key.down = down; m_key.shift = shift;
}

void CEvent_tir::update(float dt)
{
  (void)dt;
}
