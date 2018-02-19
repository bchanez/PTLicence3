#include "CTexture_Manager.hpp"

/*explicit*/ CTexture_Manager::CTexture_Manager()
{
	LOG("CTexture_Manager Constructor\n");

	// stats
	addResource(ETexture_Name::e_Titlescreen, "rsc/graphics/titlescreen.png");
	addResource(ETexture_Name::e_Menu, "rsc/graphics/screen_menu.png");
	addResource(ETexture_Name::e_Pause, "rsc/graphics/screen_pause.png");

	// button
	addResource(ETexture_Name::e_Play, "rsc/graphics/play.png");
	addResource(ETexture_Name::e_Return, "rsc/graphics/return.png");
	addResource(ETexture_Name::e_Quit, "rsc/graphics/quit.png");

	//armes
	addResource(ETexture_Name::e_Knife, "rsc/graphics/knife.png");

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
