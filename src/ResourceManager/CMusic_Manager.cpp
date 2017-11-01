#include "CMusic_Manager.hpp"


/* explicit */ CMusic_Manager::CMusic_Manager (void)
: m_music()
{
  std::cout << "CMusic_Manager constructor\n";
}

/* virtual */ CMusic_Manager::~CMusic_Manager (void)
{
  std::cout << "CMusic_Manager destructor\n";

  m_music.clear();
}

const sf::Music& CMusic_Manager::get_music (const std::string& filename)
{
  sf::Music music;
  return music;
}

void CMusic_Manager::delete_music (const sf::Music& music)
{

}

void CMusic_Manager::delete_music (const std::string& filename)
{

}
