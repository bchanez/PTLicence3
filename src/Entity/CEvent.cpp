#include "CEvent.hpp"

/*explicit*/ CEvent::CEvent(void)
{
  LOG("CEvent Constructor\n");

  setTexture();
  setAnimation();
}

/*virtual*/ CEvent::~CEvent(void)
{
  LOG("CEvent Destructor\n");
}

// donne la texture au personnage
void CEvent::setTexture(void)
{

}

// definie les animations de l'evenement
void CEvent::setAnimation(void)
{

}

void CEvent::update(float dt)
{
  switch (m_state)
  {

    default : {} break;
  }
}
