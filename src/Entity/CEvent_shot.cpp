#include "CEvent_shot.hpp"

/*explicit*/ CEvent_shot::CEvent_shot(void)
{
  LOG("CEvent_shot Constructor\n");
}

/*virtual*/ CEvent_shot::~CEvent_shot(void)
{
  LOG("CEvent_shot Destructor\n");
}

// Give the event a texture
void CEvent_shot::setTexture(void)
{

}

//Define the event's textures
void CEvent_shot::setAnimation(void)
{

}

void CEvent_shot::input(void)
{

}

void CEvent_shot::update(bool isServer, float dt)
{
  (void)dt;
  (void)isServer;
}
