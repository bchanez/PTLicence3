#include "CIntro_State.hpp"

namespace State
{
  /*explicit*/ CIntro::CIntro(CApplication & application)
    : CGame_State(application)
  {
    LOG("CIntro Constructor\n");

    m_intro.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Titlescreen));

    for (int i = 0; i < 4 ; ++i)
      m_animation.addFrame(sf::IntRect(i * 1920, 0, 1920, 1080), 0.1f);
  }

  /*virtual*/ CIntro::~CIntro()
  {
    LOG("CIntro Destructor\n");
  }

  void CIntro::init(void)
  {
      m_key = false;
  }

  void CIntro::input(sf::Event * event)
  {
      if((* event).type == sf::Event::KeyPressed || (* event).type == sf::Event::MouseButtonPressed)
        m_key = true;
  }

  void CIntro::update(float dt)
  {
    (void)dt;

    m_intro.setTextureRect(m_animation.getFrame());

    if (m_key)
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
