#include "CMenu_State.hpp"

namespace State
{
  /*explicit*/ CMenu::CMenu(CApplication & application)
    : CGame_State(application)
  {
    LOG("CMenu Constructor\n");

    m_menu.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Menu));
  }

  /*virtual*/ CMenu::~CMenu()
  {
    LOG("CMenu Destructor\n");
  }

  void CMenu::input()
  {
  }

  void CMenu::update(float dt)
  {
  }

  void CMenu::draw()
  {
    // dessine l'image du menu
    CDisplay::draw(m_menu);
  }
}
