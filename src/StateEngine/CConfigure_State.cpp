#include "CConfigure_State.hpp"
#include <iostream>

namespace State
{
  /*explicit*/ CConfigure::CConfigure(CApplication & application)
    : CGame_State(application)
  {
    LOG("CConfigure Constructor\n");

    m_configure.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Configure));

    // bouton retour
    m_listButton.push_back(std::make_unique<CButton>(& CResourceHolder::get().texture(ETexture_Name::e_Jouer), sf::Vector2f(200,200), sf::Vector2f(200,80)));

    // bouton jouer
    m_listButton.push_back(std::make_unique<CButton>(& CResourceHolder::get().texture(ETexture_Name::e_Quitter), sf::Vector2f(200,400), sf::Vector2f(200,80)));

    // champs input nombre de pnj
    m_listInput.push_back(std::make_unique<CInput>(& CResourceHolder::get().texture(ETexture_Name::e_InputTest), sf::Vector2f(500,300), sf::Vector2f(500,166)));
  }

  /*virtual*/ CConfigure::~CConfigure()
  {
    LOG("CConfigure Destructor\n");
  }

  void CConfigure::init(void)
  {
      m_key.escape = false;

      for (unsigned int i = 0; i < m_listButton.size(); ++i)
        m_listButton[i]->init();

      for (unsigned int i = 0; i < m_listInput.size(); ++i)
        m_listInput[i]->init();
  }

  void CConfigure::input(sf::Event * event)
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
      {
        for (unsigned int i = 0; i < m_listButton.size(); ++i)
          m_listButton[i]->inputMousePosition(CDisplay::getWindow()->mapPixelToCoords(sf::Vector2i((* event).mouseMove.x, (* event).mouseMove.y), * CDisplay::getView()));

        for (unsigned int i = 0; i < m_listInput.size(); ++i)
          m_listInput[i]->inputMousePosition(CDisplay::getWindow()->mapPixelToCoords(sf::Vector2i((* event).mouseMove.x, (* event).mouseMove.y), * CDisplay::getView()));
      }

      if ((* event).type == sf::Event::MouseButtonPressed)
          if ((* event).mouseButton.button == sf::Mouse::Left)
          {
            for (unsigned int i = 0; i < m_listButton.size(); ++i)
              m_listButton[i]->inputMouseclicked(true);

            for (unsigned int i = 0; i < m_listInput.size(); ++i)
              m_listInput[i]->inputMouseclicked(true);
          }

      if ((* event).type == sf::Event::MouseButtonReleased)
          if ((* event).mouseButton.button == sf::Mouse::Left)
          {
            for (unsigned int i = 0; i < m_listButton.size(); ++i)
              m_listButton[i]->inputMouseclicked(false);

            for (unsigned int i = 0; i < m_listInput.size(); ++i)
              m_listInput[i]->inputMouseclicked(false);
          }
    }
  }

  void CConfigure::update(float dt)
  {
    (void)dt;
    // update button
    for (unsigned int i = 0; i < m_listButton.size(); ++i)
      m_listButton[i]->update(dt);

    // update input
    for (unsigned int i = 0; i < m_listInput.size(); ++i)
      m_listInput[i]->update(dt);

    // update scene
    if (m_key.escape || m_listButton[e_retour]->action())
    {
      m_application->initMenuState();
      m_application->changeState(EState::e_menu);
    }

    if (m_listButton[e_jouer]->action())
    {
      m_application->initPlayingStateNewGame(100);
      m_application->changeState(EState::e_playing);
    }
  }

  void CConfigure::draw()
  {
    // dessine l'image du menu
    CDisplay::draw(m_configure);

    //dessine les boutons
    for (unsigned int i = 0; i < m_listButton.size(); ++i)
      CDisplay::draw(* (m_listButton[i].get()));

    //dessine les inputs
    for (unsigned int i = 0; i < m_listInput.size(); ++i)
      CDisplay::draw(* (m_listInput[i].get()));
  }
}
