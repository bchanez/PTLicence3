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

  void CIntro::input(sf::Event * event)
  {
    // touche concernant l'etat
    while (CDisplay::getWindow()->pollEvent(* event))
    {
      if((* event).type == sf::Event::Closed)
          CDisplay::getWindow()->close();

      if((* event).type == sf::Event::KeyPressed)
        m_application->changeState(m_application->getMenu_State());
    }
  }

  void CIntro::update(float dt)
  {
  }

  void CIntro::draw()
  {
    // dessine l'image de l'intro
    CDisplay::draw(m_intro);
  }
}
