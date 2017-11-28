#include "CCharacter.hpp"
#include "../Tools/DEBUG.hpp"

/*explicit*/ CCharacter::CCharacter(void)
{
  LOG("CCharacter Constructor\n");

  m_position = sf::Vector2f(960.f, 540.f);
  m_sprite.setPosition(m_position);
  m_sprite.setOrigin(sf::Vector2f(20, 30));

  m_state = e_idle;
  m_orientation = e_right;

  setTexture();
  setAnimation();
}

/*virtual*/ CCharacter::~CCharacter(void)
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
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Pants_1));
  m_prerender.draw(spr);
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_TShirt_1));
  m_prerender.draw(spr);

  m_prerender.display();


  m_sprite.setTexture(m_prerender.getTexture());
}

// definie les animations du personnage
void CCharacter::setAnimation(void)
{
  for (unsigned int i = 0; i < m_nb_animation ; ++i)
    m_animation.push_back(CAnimation());

  for (int i = 0; i < 4 ; ++i)
  {
    m_animation[e_walk_right].addFrame(sf::IntRect(i * 40, 0, 40, 40), 0.1f);
    m_animation[e_walk_left].addFrame(sf::IntRect(i * 40, 40, 40, 40), 0.1f);
  }
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

      // mise a jour de l'animation
      if (m_orientation == e_right)
      {
        m_animation[e_walk_right].restart();
        m_sprite.setTextureRect(m_animation[e_walk_right].getCurrentFrame());
      }
      else if (m_orientation == e_left)
      {
        m_animation[e_walk_left].restart();
        m_sprite.setTextureRect(m_animation[e_walk_left].getCurrentFrame());
      }
    }
    break;

    case e_walk :
    {
      m_move_speed = WALK_SPEED;
      if(m_input.getButton().left) { m_position.x += -(m_move_speed * dt); m_orientation = e_left; }
      if(m_input.getButton().right) { m_position.x += m_move_speed * dt; m_orientation = e_right; }
      if(m_input.getButton().up) m_position.y += -(m_move_speed * dt);
      if(m_input.getButton().down) m_position.y += m_move_speed * dt;

      if(!m_input.getButton().left && !m_input.getButton().right && !m_input.getButton().up  && !m_input.getButton().down)
      {
        m_state = e_idle;
      }
      else
        if(m_input.getButton().shift)
          m_state = e_run;

      // mise a jour de la position
      m_sprite.setPosition(m_position);

      // mise a jour de l'animation
      if (m_orientation == e_right)
      {
        m_animation[e_walk_left].restart();
        m_sprite.setTextureRect(m_animation[e_walk_right].getFrame());
      }
      else if (m_orientation == e_left)
      {
        m_animation[e_walk_right].restart();
        m_sprite.setTextureRect(m_animation[e_walk_left].getFrame());
      }
    }
    break;

    case e_run :
    {
      m_move_speed = RUN_SPEED;
      if(m_input.getButton().left) { m_position.x += -(m_move_speed * dt); m_orientation = e_left; }
      if(m_input.getButton().right) { m_position.x += m_move_speed * dt; m_orientation = e_right; }
      if(m_input.getButton().up) m_position.y += -(m_move_speed * dt);
      if(m_input.getButton().down) m_position.y += m_move_speed * dt;

      if(!m_input.getButton().left && !m_input.getButton().right && !m_input.getButton().up  && !m_input.getButton().down)
      {
        m_state = e_idle;
      }
      else
        if(!m_input.getButton().shift)
          m_state = e_walk;

      // mise a jour de la position
      m_sprite.setPosition(m_position);

      // mise a jour de l'animation
      if (m_orientation == e_right)
      {
        m_animation[e_walk_left].restart();
        m_sprite.setTextureRect(m_animation[e_walk_right].getFrame());
      }
      else if (m_orientation == e_left)
      {
        m_animation[e_walk_right].restart();
        m_sprite.setTextureRect(m_animation[e_walk_left].getFrame());
      }
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
