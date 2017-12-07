#include "CTexture_Manager.hpp"

/*explicit*/ CTexture_Manager::CTexture_Manager()
{
	LOG("CTexture_Manager Constructor\n");

	// stats
	addResource(ETexture_Name::e_Intro, "rsc/graphics/testIntro.png");
	addResource(ETexture_Name::e_Menu, "rsc/graphics/testMenu.jpg");

	// character
	addResource(ETexture_Name::e_Characters, "rsc/graphics/potatoman.png");
	addResource(ETexture_Name::e_Hair_1, "rsc/graphics/hair_1.png");
	addResource(ETexture_Name::e_Hair_2, "rsc/graphics/hair_2.png");
	addResource(ETexture_Name::e_Hair_3, "rsc/graphics/hair_3.png");
	addResource(ETexture_Name::e_Hair_4, "rsc/graphics/hair_4.png");
	addResource(ETexture_Name::e_Hair_5, "rsc/graphics/hair_5.png");
	addResource(ETexture_Name::e_Hair_6, "rsc/graphics/hair_6.png");
	addResource(ETexture_Name::e_Hair_7, "rsc/graphics/hair_7.png");
	addResource(ETexture_Name::e_Hair_8, "rsc/graphics/hair_8.png");
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
