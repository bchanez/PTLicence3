#include "CWeapon.hpp"

CWeapon::CWeapon(void)
{
  LOG("CWeapon Constructor\n");

  m_attack = false;
  m_loop = true;

  m_sprite.setOrigin(sf::Vector2f(20, 30));

  setTexture();
  setAnimation();
}

CWeapon::~CWeapon(void)
{
  LOG("CWeapon Destructor\n");
}

void CWeapon::setTexture(void)
{
  m_sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Knife));
}

void CWeapon::setAnimation(void)
{
  m_animation.push_back(CAnimation());

  for (unsigned int i = 0; i < m_nb_animation; ++i)
    m_animation[0].addFrame(sf::IntRect(i * 40, 0, 40, 40), 0.05f);
}

void CWeapon::input(void){}

void CWeapon::update(bool isServer, float dt)
{
  if (!isServer)
    m_sprite.setTextureRect(m_animation[0].getFrame());

  if (m_animation[0].isLoopDone()){
    m_attack = false;
    m_loop = true;
  }
}

void CWeapon::attack(void)
{
  m_attack = true;

  m_animation[0].restart();

  m_loop = false;
}

bool CWeapon::isLoopDone(void)
{
  return m_loop;
}
