#include "CCharacter.hpp"

#define WALK_SPEED 1
#define RUN_SPEED 2

CCharacter::CCharacter()
{

  //Initialisation des variables
  m_sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));
  m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));

  m_state = 1;
  m_speed = sf::Vector2i(0, 0);
  m_move_speed = 1;
  m_orientation = right;
  m_shift = false;
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
      }
      break;
  }
}


void CCharacter::update(){

  switch (m_state) {
    case idle :   //Dans le cas où le personnage est à l'arrêt

      if (m_speed != sf::Vector2i(0, 0) && m_shift == true){
        m_state = run;
      }
      else if (m_speed != sf::Vector2i(0, 0)){
        m_state = walk;
      }

      m_sprite.setTextureRect(sf::IntRect(0, m_orientation*40, 40, 40));
      break;

    case walk :   //Dans le cas où le personnage se déplace

      //Mise à jour de l'orientation
      if (m_speed.x > 0){
        m_orientation = right;
      }
      else if (m_speed.x < 0){
        m_orientation = left;
      }

      //Mise à jour de la texture
      m_sprite.setTextureRect(sf::IntRect((((int)m_clock.getElapsedTime().asMilliseconds()%400)/100)*40, m_orientation*40, 40, 40));
      //Mise à jour de la position
      m_sprite.move(sf::Vector2f(m_speed.x*WALK_SPEED, m_speed.y*WALK_SPEED));

      //Si le personnage est à l'arrêt, on repasse à l'état arrêt
      if (m_speed == sf::Vector2i(0, 0)){
        m_state = idle;
      }
      else if (m_shift == true){
        m_state = run;
      }

      break;

    case run :    //Dans le cas où le personnage court

      //Mise à jour de l'orientation
      if (m_speed.x > 0){
        m_orientation = right;
      }
      else if (m_speed.x < 0){
        m_orientation = left;
      }

      //Mise à jour de la texture
      m_sprite.setTextureRect(sf::IntRect((((int)m_clock.getElapsedTime().asMilliseconds()%400)/100)*40, m_orientation*40, 40, 40));
      //Mise à jour de la position
      m_sprite.move(sf::Vector2f(m_speed.x*RUN_SPEED, m_speed.y*RUN_SPEED));

      //Si le personnage est à l'arrêt, on repasse à l'état arrêt
      if (m_speed == sf::Vector2i(0, 0)){
        m_state = idle;
      }
      else if (m_shift == false){
        m_state = walk;
      }

      break;
  }

}
