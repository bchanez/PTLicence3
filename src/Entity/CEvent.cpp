#include "CEvent.hpp"

/*explicit*/ CEvent::CEvent(void)
{
  LOG("CEvent Constructor\n");
}

/*virtual*/ CEvent::~CEvent(void)
{
  LOG("CEvent Destructor\n");
}

// donne la texture a l'evenemnt
void CEvent::setTexture(void) {}

// definie les animations de l'evenement
void CEvent::setAnimation(void) {}

void CEvent::update(float dt) {}
