#include "CResult_State.hpp"

namespace State
{
  /*explicit*/ CResult::CResult(CApplication & application)
    : CGame_State(application)
  {
    LOG("CResult Constructor\n");

    // bouton retour
    m_listButton.push_back(std::make_unique<CButton>(& CResourceHolder::get().texture(ETexture_Name::e_Return), sf::Vector2f(860,700), sf::Vector2f(200,80)));

  }

  /*virtual*/ CResult::~CResult()
  {
    LOG("CResult Destructor\n");
  }

  void CResult::init(void)
  {
      m_key.escape = false;

      for (unsigned int i = 0; i < m_listButton.size(); ++i)
        m_listButton[i]->init();

      //Recentre la vue (différente de en jeu)
      CDisplay::getView()->setSize(1920.f, 1080.f);
      CDisplay::getView()->setCenter(1920.f/2, 1080.f/2);
      CDisplay::getWindow()->setView(* CDisplay::getView());
  }

  void CResult::input(sf::Event * event)
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

  void CResult::update(float dt)
  {
    (void)dt;
    // update button
    for (unsigned int i = 0; i < m_listButton.size(); ++i)
      m_listButton[i]->update(dt);

    // update scene
    if (m_key.escape || m_listButton[e_retour]->action())
    {
      m_application->initState(EState::e_menu);
      m_application->changeState(EState::e_menu);
    }
  }

  void CResult::draw()
  {
    // dessine l'image de resultat
    CDisplay::draw(m_result);

    //dessine les boutons
    for (unsigned int i = 0; i < m_listButton.size(); ++i)
      CDisplay::draw(* (m_listButton[i].get()));
  }

  void CResult::setResult(std::string str)
  {
    if("lose" == str)
      m_result.setTexture(CResourceHolder::get().texture(ETexture_Name::e_ResultLose));
    else
      m_result.setTexture(CResourceHolder::get().texture(ETexture_Name::e_ResultWin));
  }
}
