#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "CResourceManager.hpp"
#include "../Tools/DEBUG.hpp"

enum class ETexture_Name
{
	//stats
	e_Titlescreen,
	e_Menu,
	e_Pause,
	e_ResultLose,
	e_ResultWin,

	//button
	e_Play,
	e_Return,
	e_Quit,

	//armes
	e_Knife,

	//input
	e_InputTest,

	// events
	e_Pub,

	// map
	e_TileMap_Grass,

	//PNJ
	e_PDead
};

class CTexture_Manager : public CResourceManager<ETexture_Name, sf::Texture>
{
	public:
		explicit CTexture_Manager();
		virtual ~CTexture_Manager();

	private:
		std::map <ETexture_Name, sf::Texture> m_textures;

};
