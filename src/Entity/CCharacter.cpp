#include "CCharacter.hpp"

#define WALK_SPEED 60
#define RUN_SPEED 120

CCharacter::CCharacter()
{

  //Création de la texture du personnage
  m_prerender.create(160, 80);
  m_prerender.clear(sf::Color::Transparent);

  sf::Sprite spr;
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));
  m_prerender.draw(spr);
  spr.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Hair_5));
  m_prerender.draw(spr);
  m_prerender.display();

  //Application de la texture
  m_sprite.setTexture(m_prerender.getTexture());
  m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));

  //Initialisation des variables
  m_state = 1;
  m_speed = sf::Vector2i(0, 0);
  m_move_speed = 1;
  m_orientation = right;
  m_shift = false;

  m_sprite.setOrigin(sf::Vector2f(20, 30));
}

void CCharacter::getEvent(sf::Event &event)
{

  switch (event.type)
  {
    //On récupère les touches appuyées
    case sf::Event::KeyPressed :
      switch (event.key.code)
      {
          case sf::Keyboard::Z :
            m_speed.y += -m_move_speed;
            break;

          case sf::Keyboard::Q :
            m_speed.x += -m_move_speed;
            break;

          case sf::Keyboard::S :
            m_speed.y += m_move_speed;
            break;

          case sf::Keyboard::D :
            m_speed.x += m_move_speed;
            break;

          case sf::Keyboard::LShift :
            m_shift = true;
            break;

          default :
            break;
      }
      break;

    //On récupère les touches relâchées
    case sf::Event::KeyReleased :
      switch (event.key.code)
      {
          case sf::Keyboard::Z :
            m_speed.y -= -m_move_speed;
            break;

          case sf::Keyboard::Q :
            m_speed.x -= -m_move_speed;
            break;

          case sf::Keyboard::S :
            m_speed.y -= m_move_speed;
            break;

          case sf::Keyboard::D :
            m_speed.x -= m_move_speed;
            break;

          case sf::Keyboard::LShift :
            m_shift = false;
            break;

          default :
            break;
      }
      break;

    default :
      break;
  }
}


void CCharacter::update()
{

  float time_delta = m_move_clock.restart().asSeconds();

  switch (m_state)
  {
    case idle :   //Dans le cas où le personnage est à l'arrêt

      if (m_speed != sf::Vector2i(0, 0) && m_shift == true)
      {
        m_state = run;
        m_move_clock.restart();
      }
      else if (m_speed != sf::Vector2i(0, 0))
      {
        m_state = walk;
        m_move_clock.restart();
      }

      m_sprite.setTextureRect(sf::IntRect(0, m_orientation*40, 40, 40));
      break;

    case walk :   //Dans le cas où le personnage se déplace

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
      m_sprite.move(sf::Vector2f(m_speed.x*WALK_SPEED*time_delta, m_speed.y*WALK_SPEED*time_delta));

      //Si le personnage est à l'arrêt, on repasse à l'état arrêt
      if (m_speed == sf::Vector2i(0, 0))
      {
        m_state = idle;
      }
      else if (m_shift == true)
      {
        m_state = run;
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
      if (m_speed == sf::Vector2i(0, 0))
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