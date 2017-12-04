#include "CEvent_pub.hpp"

/*explicit*/ CEvent_pub::CEvent_pub(void)
{
  LOG("CEvent_pub Constructor\n");
}

/*virtual*/ CEvent_pub::~CEvent_pub(void)
{
  LOG("CEvent_pub Destructor\n");
}

// donne la texture a l'evenemnt
void CEvent_pub::setTexture(void) {}

// definie les animations de l'evenement
void CEvent_pub::setAnimation(void) {}

void CEvent_pub::update(float dt) {}
