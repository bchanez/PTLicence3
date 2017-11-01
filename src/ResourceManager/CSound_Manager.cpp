#include "CSound_Manager.hpp"


/* explicit */ CSound_Manager::CSound_Manager(void)
: m_sound()
{
  std::cout << "CSound_Manager constructor\n";
}

/* virtual */ CSound_Manager::~CSound_Manager (void)
{
  std::cout << "CSound_Manager destructor\n";

  m_sound.clear();
}

const sf::Sound& CSound_Manager::get_sound (const std::string& filename)
{
  sf::Sound sound;
  return sound;
}

void CSound_Manager::delete_sound (const sf::Sound& sound)
{

}

void CSound_Manager::delete_sound (const std::string& filename)
{

}
