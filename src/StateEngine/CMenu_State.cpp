#include "CMenu_State.hpp"
#include <iostream>

namespace State
{
  /*explicit*/ CMenu::CMenu(CApplication & application)
    : CGame_State(application)
  {
    LOG("CMenu Constructor\n");

    m_menu.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Menu));

    // bouton jouer
    m_listButton.push_back(std::make_unique<CButton>(& CResourceHolder::get().texture(ETexture_Name::e_Jouer), sf::Vector2f(200,200), sf::Vector2f(200,80)));

    // bouton quitter
    m_listButton.push_back(std::make_unique<CButton>(& CResourceHolder::get().texture(ETexture_Name::e_Quitter), sf::Vector2f(200,400), sf::Vector2f(200,80)));

  }

  /*virtual*/ CMenu::~CMenu()
  {
    LOG("CMenu Destructor\n");
  }

  void CMenu::init(void)
  {
      m_key.escape = false;

      for (unsigned int i = 0; i < m_listButton.size(); ++i)
        m_listButton[i]->init();

  }

  void CMenu::input(sf::Event * event)
  {
    while (CDisplay::getWindow()->pollEvent(* event))
    {
      if((* event).type == sf::Event::KeyPressed)
        if ((* event).key.code == sf::Keyboard::Escape)
          m_key.escape = true;

      if((* event).type == sf::Event::KeyReleased)
        if ((* event).key.code == sf::Keyboard::Escape)
          m_key.escape = false;

      if ((* event).type == sf::Event::MouseMoved)
        for (unsigned int i = 0; i < m_listButton.size(); ++i)
          m_listButton[i]->inputMousePosition(CDisplay::getWindow()->mapPixelToCoords(sf::Vector2i((* event).mouseMove.x, (* event).mouseMove.y), * CDisplay::getView()));

      if ((* event).type == sf::Event::MouseButtonPressed)
          if ((* event).mouseButton.button == sf::Mouse::Left)
            for (unsigned int i = 0; i < m_listButton.size(); ++i)
              m_listButton[i]->inputMouseclicked(true);

      if ((* event).type == sf::Event::MouseButtonReleased)
          if ((* event).mouseButton.button == sf::Mouse::Left)
            for (unsigned int i = 0; i < m_listButton.size(); ++i)
              m_listButton[i]->inputMouseclicked(false);
    }
  }

  void CMenu::update(float dt)
  {
    (void)dt;
    // update button
    for (unsigned int i = 0; i < m_listButton.size(); ++i)
      m_listButton[i]->update(dt);

    // update scene
    if (m_key.escape || m_listButton[e_quitter]->action())
      CDisplay::getWindow()->close();

    if (m_listButton[e_configure]->action())
    {
      m_application->initConfigureState();
      m_application->changeState(EState::e_configure);
    }
  }

  void CMenu::draw()
  {
    // dessine l'image du menu
    CDisplay::draw(m_menu);

    //dessine les boutons
    for (unsigned int i = 0; i < m_listButton.size(); ++i)
      CDisplay::draw(* (m_listButton[i].get()));
  }
}
