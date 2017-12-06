#include "CIntro_State.hpp"

namespace State
{
  /*explicit*/ CIntro::CIntro(CApplication & application)
    : CGame_State(application)
  {
    LOG("CIntro Constructor\n");
  }

  /*virtual*/ CIntro::~CIntro()
  {
    LOG("CIntro Destructor\n");
  }

  void CIntro::input()
  {
  }

  void CIntro::update(float dt)
  {
  }

  void CIntro::draw()
  {
  }
}
