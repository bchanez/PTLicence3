#include "CFont_Manager.hpp"


/* explicit */ CFont_Manager::CFont_Manager (void)
: m_font()
{
  std::cout << "CFont_Manager constructor\n";
}

/* virtual */ CFont_Manager::~CFont_Manager (void)
{
  std::cout << "CFont_Manager destructor\n";

  m_font.clear();
}

const sf::Font& CFont_Manager::get_font (const std::string& filename)
{
  sf::Font font;
  return font;
}

void CFont_Manager::delete_font (const sf::Font& font)
{

}

void CFont_Manager::delete_font (const std::string& filename)
{

}
