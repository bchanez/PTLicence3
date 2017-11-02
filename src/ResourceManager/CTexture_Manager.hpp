#ifndef CTEXTURE_MANAGER_HPP_
#define CTEXTURE_MANAGER_HPP_

#include "SFML/Graphics.hpp"
#include <map>
#include "CResourceManager.hpp"

enum class ETexture_Name
{
	e_Characters
};

class CTexture_Manager : public CResourceManager<ETexture_Name, sf::Texture>
{
	public:
		CTexture_Manager();

	private:
		std::map <ETexture_Name, sf::Texture> m_textures;

};

#endif
