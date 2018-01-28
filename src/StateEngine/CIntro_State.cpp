#include "CIntro_State.hpp"

namespace State
{
  /*explicit*/ CIntro::CIntro(CApplication & application)
    : CGame_State(application)
  {
    LOG("CIntro Constructor\n");

    m_intro.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Titlescreen)); //Init texture

    for (int i = 0; i < 4 ; ++i)
      m_animation.addFrame(sf::IntRect(i * 1920, 0, 1920, 1080), 0.1f); //init animation
  }

  /*virtual*/ CIntro::~CIntro()
  {
    LOG("CIntro Destructor\n");
  }

  void CIntro::init(void)
  {
      m_key = false;    //Aucune touche n'est appuyée
  }

  void CIntro::input(sf::Event * event)
  {
      if((* event).type == sf::Event::KeyPressed || (* event).type == sf::Event::MouseButtonPressed) //Test si on appuie sur une touche
        m_key = true;
  }

  void CIntro::update(float dt)
  {
    (void)dt;

    m_intro.setTextureRect(m_animation.getFrame()); //Animation

    if (m_key)  //Change d'état si une touche est appuyée
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
