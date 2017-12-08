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

  void CMenu::input(sf::Event * event)
  {
    // touche concernant l'etat
    while (CDisplay::getWindow()->pollEvent(* event))
    {
      if ((* event).type == sf::Event::Closed)
          CDisplay::getWindow()->close();

      if((* event).type == sf::Event::KeyPressed)
      {
        if((* event).key.code == sf::Keyboard::Escape)
          CDisplay::getWindow()->close();

        if((* event).type == sf::Event::KeyPressed::Space)
          m_application->changeState(m_application->getPlaying_State())
      }
    }
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
