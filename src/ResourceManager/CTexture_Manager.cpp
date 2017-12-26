#include "CTexture_Manager.hpp"

/*explicit*/ CTexture_Manager::CTexture_Manager()
{
	LOG("CTexture_Manager Constructor\n");

	// stats
	addResource(ETexture_Name::e_Intro, "rsc/graphics/intro.png");
	addResource(ETexture_Name::e_Menu, "rsc/graphics/menu.png");
	addResource(ETexture_Name::e_Configure, "rsc/graphics/configure.png");
		addResource(ETexture_Name::e_Pause, "rsc/graphics/pause.png");

	// button
	addResource(ETexture_Name::e_ButtonTest, "rsc/graphics/buttonTest.jpg");


	// character
	addResource(ETexture_Name::e_Characters, "rsc/graphics/potatoman.png");
	addResource(ETexture_Name::e_TShirt_1, "rsc/graphics/tshirt_1.png");
	addResource(ETexture_Name::e_Pants_1, "rsc/graphics/pants_1.png");

	//events
	addResource(ETexture_Name::e_Pub, "rsc/graphics/pub.png");

	// map
	addResource(ETexture_Name::e_TileMap_Grass, "rsc/graphics/tilemap_grass.png");


}

/*virtual*/ CTexture_Manager::~CTexture_Manager()
{
	LOG("CTexture_Manager Destructor\n");
}
