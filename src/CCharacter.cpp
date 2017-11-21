#include "CCharacter.hpp"

#define RUN_SPEED 2

CCharacter::CCharacter(){

  //Initialisation des variables
  m_sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));
  m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));

  m_state = 1;
  m_speed = sf::Vector2i(0, 0);
  m_move_speed = 1;
  m_orientation = right;
  m_shift = false;
}

void CCharacter::getEvent(sf::Event &event){

  //On récupère les touches appuyées
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Z )
    {
      m_speed.y += -m_move_speed;
    }
    if (event.key.code == sf::Keyboard::Q)
    {
      m_speed.x += -m_move_speed;
    }
    if (event.key.code == sf::Keyboard::S)
    {
      m_speed.y += m_move_speed;
    }
    if (event.key.code == sf::Keyboard::D)
    {
      m_speed.x += m_move_speed;
    }
    if (event.key.code == sf::Keyboard::LShift)
    {
      m_shift = true;
    }
  }

  //On récupère les touches relâchées
  if (event.type == sf::Event::KeyReleased)
  {
    if (event.key.code == sf::Keyboard::Z)
    {
      m_speed.y -= -m_move_speed;
    }
    if (event.key.code == sf::Keyboard::Q)
    {
      m_speed.x -= -m_move_speed;
    }
    if (event.key.code == sf::Keyboard::S)
    {
      m_speed.y -= m_move_speed;
    }
    if (event.key.code == sf::Keyboard::D)
    {
      m_speed.x -= m_move_speed;
    }
    if (event.key.code == sf::Keyboard::LShift)
    {
      m_shift = false;
    }
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
      m_sprite.move(sf::Vector2f(m_speed.x*(int)m_move_speed, m_speed.y*(int)m_move_speed));

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
      m_sprite.move(sf::Vector2f(m_speed.x*(int)m_move_speed*RUN_SPEED, m_speed.y*(int)m_move_speed*RUN_SPEED));

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
