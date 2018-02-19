#include "CEvent_fire.hpp"

/*explicit*/ CEvent_fire::CEvent_fire(void)
{
  LOG("CEvent_fire Constructor\n");
}

/*virtual*/ CEvent_fire::~CEvent_fire(void)
{
  LOG("CEvent_fire Destructor\n");
}

// Give the event a texture
void CEvent_fire::setTexture(void)
{

}

//Define the event's textures
void CEvent_fire::setAnimation(void)
{

}

void CEvent_fire::input(void)
{

}

void CEvent_fire::update(bool isServer, float dt)
{
  (void)dt;
  (void)isServer;
}
