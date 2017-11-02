#include "CFont_Manager.hpp"


/* explicit */ CFont_Manager::CFont_Manager (void)
: m_fonts()
{
  std::cout << "CFont_Manager constructor\n";
}

/* virtual */ CFont_Manager::~CFont_Manager (void)
{
  std::cout << "CFont_Manager destructor\n";

  m_fonts.clear();
}

const sf::Font& CFont_Manager::get_font (const std::string& filename)
{
  // check if the font already exist and return it
  for (std::map<std::string, sf::Font>::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
    if (filename.compare(it->first) == 0)
      return it->second;

  // else add and return it (if font is found)
  sf::Font font;
  for (std::vector<std::string>::iterator it = m_resourceDirectories.begin(); it != m_resourceDirectories.end(); ++it)
    if (font.loadFromFile(*it + filename))
    {
      m_fonts[filename] = font;
      return m_fonts[filename];
    }

  // else font is not found
  return font;
}

void CFont_Manager::delete_font (const sf::Font& font)
{
  // check if font exist and delete it
  for (std::map<std::string, sf::Font>::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
		if (&font == &it->second)
		{
			m_fonts.erase(it);
      return;
		}
}

void CFont_Manager::delete_font (const std::string& filename)
{
  // check if path of font exist and delete it
  std::map<std::string, sf::Font>::iterator it = m_fonts.find(filename);
  if (it != m_fonts.end())
    m_fonts.erase(it);
}
