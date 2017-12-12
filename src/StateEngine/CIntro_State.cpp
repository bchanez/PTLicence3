#include "CIntro_State.hpp"

namespace State
{
  /*explicit*/ CIntro::CIntro(CApplication & application)
    : CGame_State(application)
  {
    LOG("CIntro Constructor\n");

    m_intro.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Intro));
  }

  /*virtual*/ CIntro::~CIntro()
  {
    LOG("CIntro Destructor\n");
  }

  void CIntro::init(void)
  {
      m_button = false;
  }

  void CIntro::input(sf::Event * event)
  {
    // event de la scene
    if((* event).type == sf::Event::KeyPressed)
      m_button = true;
  }

  void CIntro::update(float dt)
  {
    (void)dt;

    if (m_button)
    {
      m_application->initMenuState();
      m_application->changeState(EState::e_menu);
    }
  }

  void CIntro::draw()
  {
    // dessine l'image de l'intro
    CDisplay::draw(m_intro);
  }
}
