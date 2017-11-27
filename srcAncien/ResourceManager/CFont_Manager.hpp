#ifndef CFONT_MANAGER_HPP_
#define CFONT_MANAGER_HPP_

#include "SFML/Graphics.hpp"
#include <map>
#include "CResourceManager.hpp"

enum class EFont_Name
{
};

class CFont_Manager : public CResourceManager<EFont_Name, sf::Font>
{
	public:
		CFont_Manager();

	private:
		std::map <EFont_Name, sf::Font> m_fonts;
};

#endif
