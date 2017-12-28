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

void CEvent_feu::input(sf::Event * event)
{

}

void CEvent_feu::update(float dt)
{
  (void)dt;
}
