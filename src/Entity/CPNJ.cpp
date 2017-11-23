#include "CPNJ.hpp"

#define WALK_SPEED 60
#define RUN_SPEED 120

CPNJ::CPNJ()
{

  //Création de la texture du personnage
  m_prerender.create(160, 80);
  m_prerender.clear(sf::Color::Transparent);

  sf::Sprite spr;
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));
  m_prerender.draw(spr);

  unsigned int hair = rand()%8+1;
  spr.setTexture(CResourceHolder::get().texture(static_cast<ETexture_Name>(hair)));

  m_prerender.draw(spr);
  m_prerender.display();

  //Application de la texture
  m_sprite.setTexture(m_prerender.getTexture());
  m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));


  //Initialisation des variables
  m_state = 1;
  m_speed = sf::Vector2f(0, 0);
  m_move_speed = 1;
  m_orientation = right;
  m_shift = false;

  m_sprite.setOrigin(sf::Vector2f(20, 30));
}

void CPNJ::IA()
{

  unsigned int r;

  //Si IDLE, on choisit une position aléatoire où se déplacer
  if ((r = rand()%1000) == 0 && m_state == idle)
  {
    m_goal_point = sf::Vector2i(rand()%400 -200, rand()%400 -200);
  }
  else if ((r = rand()%1000) == 1 && m_state == idle)
  {
    m_orientation = 1 - m_orientation;
  }

}


void CPNJ::update()
{

  IA();

  float time_delta = m_move_clock.restart().asSeconds();
  sf::Vector2f distance = sf::Vector2f(static_cast<unsigned int>(m_goal_point.x - m_sprite.getPosition().x), static_cast<unsigned int>(m_goal_point.y - m_sprite.getPosition().y));


  switch (m_state)
  {
    case idle :   //Dans le cas où le personnage est à l'arrêt

      if (static_cast<sf::Vector2i>(m_sprite.getPosition()) != m_goal_point){
        m_state = walk;
      }

      m_sprite.setTextureRect(sf::IntRect(0, m_orientation*40, 40, 40));
      break;

    case walk :   //Dans le cas où le personnage se déplace

      if (m_goal_point.x < m_sprite.getPosition().x)
      {
        m_speed.x = -1;
      }
      else if (m_goal_point.x > m_sprite.getPosition().x)
      {
        m_speed.x = 1;
      }
      else
      {
        m_speed.x = 0;
      }

      if ((int)m_goal_point.y < m_sprite.getPosition().y)
      {
        m_speed.y = -1;
      }
      else if ((int)m_goal_point.y > m_sprite.getPosition().y)
      {
        m_speed.y = 1;
      }
      else
      {
        m_speed.y = 0;
      }

      //Mise à jour de l'orientation
      if (m_speed.x > 0)
      {
        m_orientation = right;
      }
      else if (m_speed.x < 0)
      {
        m_orientation = left;
      }

      //Mise à jour de la texture
      m_sprite.setTextureRect(sf::IntRect(((static_cast<int>(m_clock.getElapsedTime().asMilliseconds())%400)/100)*40, m_orientation*40, 40, 40));
      //Mise à jour de la position


      if (distance.x >= static_cast<unsigned int>(m_speed.x)*WALK_SPEED*time_delta && distance.y >= static_cast<unsigned int>(m_speed.y)*WALK_SPEED*time_delta)
      {
        m_sprite.move(sf::Vector2f(m_speed.x*WALK_SPEED*time_delta, m_speed.y*WALK_SPEED*time_delta));
      }
      else if (distance.x < static_cast<unsigned int>(m_speed.x)*WALK_SPEED*time_delta && distance.y < static_cast<unsigned int>(m_speed.y)*WALK_SPEED*time_delta)
      {
        m_sprite.move(sf::Vector2f(m_goal_point.x - m_sprite.getPosition().x, m_goal_point.y - m_sprite.getPosition().y));
      }
      else if (distance.y < static_cast<unsigned int>(m_speed.y)*WALK_SPEED*time_delta)
      {
        m_sprite.move(sf::Vector2f(m_speed.x*WALK_SPEED*time_delta, m_goal_point.y - m_sprite.getPosition().y));
      }
      else if (distance.x < static_cast<unsigned int>(m_speed.x)*WALK_SPEED*time_delta)
      {
        m_sprite.move(sf::Vector2f(m_goal_point.x - m_sprite.getPosition().x, m_speed.y*WALK_SPEED*time_delta));
      }

      //Si le personnage est à l'arrêt, on repasse à l'état arrêt
      if (m_goal_point == (sf::Vector2i)m_sprite.getPosition()){
        m_state = idle;
      }


      break;

    case run :    //Dans le cas où le personnage court

      //Mise à jour de l'orientation
      if (m_speed.x > 0)
      {
        m_orientation = right;
      }
      else if (m_speed.x < 0)
      {
        m_orientation = left;
      }

      //Mise à jour de la texture
      m_sprite.setTextureRect(sf::IntRect(((static_cast<int>(m_clock.getElapsedTime().asMilliseconds())%400)/100)*40, m_orientation*40, 40, 40));
      //Mise à jour de la position
      m_sprite.move(sf::Vector2f(m_speed.x*RUN_SPEED*time_delta, m_speed.y*RUN_SPEED*time_delta));

      //Si le personnage est à l'arrêt, on repasse à l'état arrêt
      if (m_speed == sf::Vector2f(0, 0))
      {
        m_state = idle;
      }
      else if (m_shift == false)
      {
        m_state = walk;
      }

      break;
  }

}
