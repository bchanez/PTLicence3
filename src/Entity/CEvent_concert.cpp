#include "CEvent_concert.hpp"

/*explicit*/ CEvent_concert::CEvent_concert(void)
{
  LOG("CEvent_concert Constructor\n");
}

/*virtual*/ CEvent_concert::~CEvent_concert(void)
{
  LOG("CEvent_concert Destructor\n");
}

//Give the event a texture
void CEvent_concert::setTexture(void)
{

}

// Define the event's animation
void CEvent_concert::setAnimation(void)
{

}

void CEvent_concert::input()
{
}

void CEvent_concert::update(bool isServer, float dt)
{
  (void)dt;
  (void)isServer;
}
