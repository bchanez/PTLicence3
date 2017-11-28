#include "CEntity.hpp"
#include "../Tools/DEBUG.hpp"

CEntity::CEntity(void)
{
  LOG("CEntity Constructor\n");
}

CEntity::~CEntity(void)
{
  LOG("CEntity Destructor\n");
}

void CEntity::setTexture(void) {}

void CEntity::update(float dt) {}
