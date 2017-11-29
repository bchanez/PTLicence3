#include "CEntity.hpp"
#include "../Tools/DEBUG.hpp"

/*explicit*/ CEntity::CEntity(void)
{
  LOG("CEntity Constructor\n");
}

/*virtual*/ CEntity::~CEntity(void)
{
  LOG("CEntity Destructor\n");
}

/*virtual*/ void CEntity::setTexture(void) {}

/*virtual*/ void CEntity::update(float dt) {}
