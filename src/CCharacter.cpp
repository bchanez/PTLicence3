#include "CCharacter.hpp"

CCharacter::CCharacter(){

  m_sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));
  m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));

  m_state = 1;
  m_speed = sf::Vector2i(0, 0);
  m_move_speed = 1;
  m_orientation = right;
}

void CCharacter::getEvent(sf::Event &event){

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
  }

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
  }
}


void CCharacter::update(){

  switch (m_state) {
    case idle :

      if (m_speed != sf::Vector2i(0, 0)) {
        m_state = walk;
        std::cout << std::endl;
      }

      m_sprite.setTextureRect(sf::IntRect(0, m_orientation*40, 40, 40));
      break;

    case walk :

      if (m_speed.x > 0){
        m_orientation = right;
      }
      else if (m_speed.x < 0){
        m_orientation = left;
      }

      m_sprite.setTextureRect(sf::IntRect((((int)m_clock.getElapsedTime().asMilliseconds()%400)/100)*40, m_orientation*40, 40, 40));

      m_sprite.move((sf::Vector2f)m_speed);

      if (m_speed == sf::Vector2i(0, 0)) {
        m_state = idle;
        std::cout << std::endl;
      }

      break;
  }

}
