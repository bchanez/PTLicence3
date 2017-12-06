#include "CMenu_State.hpp"

namespace State
{
  /*explicit*/ CMenu::CMenu(CApplication & application)
    : CGame_State(application)
  {
    LOG("CMenu Constructor\n");
  }

  /*virtual*/ CMenu::~CMenu()
  {
    LOG("CMenu Destructor\n");
  }

  void CMenu::CMenu()
  {
  }

  void CMenu::update(float dt)
  {
  }

  void CMenu::draw()
  {
  }
}
