#include "CPNJ.hpp"
#include "../Tools/DEBUG.hpp"

CPNJ::CPNJ()
{
  LOG("CPNJ Constructor\n");
}

CPNJ::~CPNJ()
{
  LOG("CPNJ Destructor\n");
}

void CPNJ::IA()
{

}


void CPNJ::update(float dt)
{
  switch (m_state)
  {
    case idle :
    {

    }
    break;

    case walk :
    {

    }
    break;

    case run :
    {

    }
    break;

    case wander :
    {

    }
    break;

    case action :
    {

    }
    break;

    case question :
    {

    }
    break;

    case dead :
    {

    }
    break;

    case disappear :
    {

    }
    break;

    default : {} break;
  }
}
