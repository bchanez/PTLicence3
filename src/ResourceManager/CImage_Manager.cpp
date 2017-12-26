#include "CImage_Manager.hpp"

/*explicit*/ CImage_Manager::CImage_Manager()
{
	LOG("CImage_Manager Constructor\n");

	// character
	addResource(EImage_Name::e_Hair_1, "rsc/graphics/hair_1.png");
	addResource(EImage_Name::e_Hair_2, "rsc/graphics/hair_2.png");
	addResource(EImage_Name::e_Hair_3, "rsc/graphics/hair_3.png");
	addResource(EImage_Name::e_Hair_4, "rsc/graphics/hair_4.png");
	addResource(EImage_Name::e_Hair_5, "rsc/graphics/hair_5.png");
	addResource(EImage_Name::e_Hair_6, "rsc/graphics/hair_6.png");
	addResource(EImage_Name::e_Hair_7, "rsc/graphics/hair_7.png");
	addResource(EImage_Name::e_Hair_8, "rsc/graphics/hair_8.png");
}

/*virtual*/ CImage_Manager::~CImage_Manager()
{
	LOG("CImage_Manager Destructor\n");
}
