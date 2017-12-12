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

  void CMenu::init(void)
  {
      m_button.escape = m_button.space = false;
  }

  void CMenu::input(sf::Event * event)
  {
    // event de la scene
    if((* event).type == sf::Event::KeyPressed)
    {
      if ((* event).key.code == sf::Keyboard::Escape)
        m_button.escape = true;

      if ((* event).key.code == sf::Keyboard::Space)
        m_button.space = true;
    }

    if((* event).type == sf::Event::KeyReleased)
    {
      if ((* event).key.code == sf::Keyboard::Escape)
        m_button.escape = false;

      if ((* event).key.code == sf::Keyboard::Space)
        m_button.space = false;
    }
  }

  void CMenu::update(float dt)
  {
    (void)dt;

    if (m_button.escape)
      CDisplay::getWindow()->close();

    if (m_button.space)
    {
      m_application->initPlayingState(100);
      m_application->changeState(EState::e_playing);
    }
  }

  void CMenu::draw()
  {
    // dessine l'image du menu
    CDisplay::draw(m_menu);
  }
}
