#ifndef CTEXTURE_MANAGER_HPP_
#define CTEXTURE_MANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include "CResourceManager.hpp"
#include "../Tools/DEBUG.hpp"

enum class ETexture_Name
{
	e_Characters,
	e_Hair_1,
	e_Hair_2,
	e_Hair_3,
	e_Hair_4,
	e_Hair_5,
	e_Hair_6,
	e_Hair_7,
	e_Hair_8,
	e_TShirt_1,
	e_Pants_1,
	e_TileMap_Grass
};

class CTexture_Manager : public CResourceManager<ETexture_Name, sf::Texture>
{
	public:
		explicit CTexture_Manager();
		virtual ~CTexture_Manager();

	private:
		std::map <ETexture_Name, sf::Texture> m_textures;

};

#endif
