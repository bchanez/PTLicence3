#include "CCharacter.hpp"
#include "../Tools/DEBUG.hpp"

CCharacter::CCharacter(void)
{
  LOG("CCharacter Constructor\n");

  m_position = sf::Vector2f(0.f, 0.f);
  m_move_speed = 1;

  m_state = e_idle;
  m_orientation = e_right;

  setTexture();
}

CCharacter::~CCharacter(void)
{
  LOG("CCharacter Destructor\n");
}

// donne la texture au personnage
void CCharacter::setTexture(void)
{
  m_prerender.create(160, 80);
  m_prerender.clear(sf::Color::Transparent);

  sf::Sprite spr;
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));
  m_prerender.draw(spr);
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Hair_5));
  m_prerender.draw(spr);
  /*
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Pants_1));
  m_prerender.draw(spr);
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_TShirt_1));
  m_prerender.draw(spr);*/

  m_prerender.display();


  m_sprite.setTexture(m_prerender.getTexture());
}

CInput& CCharacter::getInput(void)
{
  return m_input;
}

void CCharacter::update(float dt)
{
  switch (m_state)
  {
    case e_idle :
    {
      if(m_input.getButton().left || m_input.getButton().right || m_input.getButton().up || m_input.getButton().down)
      {
        if (!m_input.getButton().shift)
          m_state = e_walk;
        else
          m_state = e_run;
      }
    }
    break;

    case e_walk :
    {
      if(m_input.getButton().left) { m_position.x += -(m_move_speed * WALK_SPEED * dt); m_orientation = e_left; }
      if(m_input.getButton().right) { m_position.x += m_move_speed * WALK_SPEED * dt; m_orientation = e_right; }
      if(m_input.getButton().up) m_position.y += -(m_move_speed * WALK_SPEED * dt);
      if(m_input.getButton().down) m_position.y += m_move_speed * WALK_SPEED * dt;

      if(!m_input.getButton().left && !m_input.getButton().right && !m_input.getButton().up  && !m_input.getButton().down)
        m_state = e_idle;
      else
        if(m_input.getButton().shift)
          m_state = e_run;

      // mise a jour de la position
      m_sprite.setPosition(m_position);
    }
    break;

    case e_run :
    {
      if(m_input.getButton().left) { m_position.x += -(m_move_speed * RUN_SPEED * dt); m_orientation = e_left; }
      if(m_input.getButton().right) { m_position.x += m_move_speed * RUN_SPEED * dt; m_orientation = e_right; }
      if(m_input.getButton().up) m_position.y += -(m_move_speed * RUN_SPEED * dt);
      if(m_input.getButton().down) m_position.y += (m_move_speed * RUN_SPEED * dt);

      if(!m_input.getButton().left && !m_input.getButton().right && !m_input.getButton().up  && !m_input.getButton().down)
        m_state = e_idle;
      else
        if(!m_input.getButton().shift)
          m_state = e_walk;

      // mise a jour de la position
      m_sprite.setPosition(m_position);
    }
    break;

    case e_action :
    {

    }
    break;

    case e_dead :
    {

    }
    break;

    case e_disappear :
    {

    }
    break;

    default : {} break;
  }
}
