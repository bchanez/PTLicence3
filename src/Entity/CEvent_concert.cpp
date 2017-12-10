#include "CEvent_concert.hpp"

/*explicit*/ CEvent_concert::CEvent_concert(void)
{
  LOG("CEvent_concert Constructor\n");
}

/*virtual*/ CEvent_concert::~CEvent_concert(void)
{
  LOG("CEvent_concert Destructor\n");
}

// donne la texture a l'evenemnt
void CEvent_concert::setTexture(void)
{
  
}

// definie les animations de l'evenement
void CEvent_concert::setAnimation(void)
{

}

void CEvent_concert::update(float dt)
{
  (void)dt;
}
