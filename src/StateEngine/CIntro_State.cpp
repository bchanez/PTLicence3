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

  void CIntro::input()
  {
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
