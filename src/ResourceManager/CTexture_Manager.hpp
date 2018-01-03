#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "CResourceManager.hpp"
#include "../Tools/DEBUG.hpp"

enum class ETexture_Name
{
	//stats
	e_Intro,
	e_Menu,
	e_Configure,
	e_Pause,

	//button
	e_ButtonTest,

	//input
	e_InputTest,

	// events
	e_Pub,

	// map
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
