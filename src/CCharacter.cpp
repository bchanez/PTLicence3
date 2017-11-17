#include "CCharacter.hpp"

CCharacter::CCharacter(){

  m_sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));
  m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));

  m_state = 1;
  m_speed = 0;
}

void CCharacter::update(){

  switch (m_state) {
    case idle :
      m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
      break;
    case walk :
      m_speed = 1;
      m_sprite.setTextureRect(sf::IntRect((((int)m_clock.getElapsedTime().asMilliseconds()%400)/100)*40, 0, 40, 40));
      break;
  }

}
