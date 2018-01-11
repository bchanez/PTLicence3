#include "CTexture_Manager.hpp"

/*explicit*/ CTexture_Manager::CTexture_Manager()
{
	LOG("CTexture_Manager Constructor\n");

	// stats
	addResource(ETexture_Name::e_Titlescreen, "rsc/graphics/titlescreen.png");
	addResource(ETexture_Name::e_Menu, "rsc/graphics/menu_screen.png");
	addResource(ETexture_Name::e_Pause, "rsc/graphics/pause_screen.png");

	// button
	addResource(ETexture_Name::e_Jouer, "rsc/graphics/jouer.png");
	addResource(ETexture_Name::e_Retour, "rsc/graphics/retour.png");
	addResource(ETexture_Name::e_Quitter, "rsc/graphics/quitter.png");

	// input
	addResource(ETexture_Name::e_InputTest, "rsc/graphics/inputfield.png");

	//events
	addResource(ETexture_Name::e_Pub, "rsc/graphics/pub.png");

	// map
	addResource(ETexture_Name::e_TileMap_Grass, "rsc/graphics/tilemap_grass.png");


}

/*virtual*/ CTexture_Manager::~CTexture_Manager()
{
	LOG("CTexture_Manager Destructor\n");
}
