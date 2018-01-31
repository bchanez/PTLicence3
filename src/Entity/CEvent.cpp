#include "CEvent.hpp"

/*explicit*/ CEvent::CEvent(void)
{
  LOG("CEvent Constructor\n");
  m_isAlive = false;
}

/*virtual*/ CEvent::~CEvent(void)
{
  LOG("CEvent Destructor\n");
}
