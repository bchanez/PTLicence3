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

void CEvent_tir::update(float dt)
{
  (void)dt;
}
