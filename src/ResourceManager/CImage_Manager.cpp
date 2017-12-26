#include "CImage_Manager.hpp"

/*explicit*/ CImage_Manager::CImage_Manager()
{
	LOG("CImage_Manager Constructor\n");

	//Character
	addResource(EImage_Name::e_Body_White, "rsc/graphics/potatoman_white.png");
	addResource(EImage_Name::e_Body_Details, "rsc/graphics/potatoman_details.png");
	//Hair
	addResource(EImage_Name::e_Hair_1, "rsc/graphics/hair_1.png");
	addResource(EImage_Name::e_Hair_2, "rsc/graphics/hair_2.png");
	addResource(EImage_Name::e_Hair_3, "rsc/graphics/hair_3.png");
	addResource(EImage_Name::e_Hair_4, "rsc/graphics/hair_4.png");
	addResource(EImage_Name::e_Hair_5, "rsc/graphics/hair_5.png");
	addResource(EImage_Name::e_Hair_6, "rsc/graphics/hair_6.png");
	addResource(EImage_Name::e_Hair_7, "rsc/graphics/hair_7.png");
	addResource(EImage_Name::e_Hair_8, "rsc/graphics/hair_8.png");
	//Hair
	addResource(EImage_Name::e_Hair_1_details, "rsc/graphics/hair_1_details.png");
	addResource(EImage_Name::e_Hair_2_details, "rsc/graphics/hair_2_details.png");
	addResource(EImage_Name::e_Hair_3_details, "rsc/graphics/hair_3_details.png");
	addResource(EImage_Name::e_Hair_4_details, "rsc/graphics/hair_4_details.png");
	addResource(EImage_Name::e_Hair_5_details, "rsc/graphics/hair_5_details.png");
	addResource(EImage_Name::e_Hair_6_details, "rsc/graphics/hair_6_details.png");
	addResource(EImage_Name::e_Hair_7_details, "rsc/graphics/hair_7_details.png");
	addResource(EImage_Name::e_Hair_8_details, "rsc/graphics/hair_8_details.png");
	//Clothes
	addResource(EImage_Name::e_TShirt_1, "rsc/graphics/tshirt_1.png");
	addResource(EImage_Name::e_Pants_1, "rsc/graphics/pants_1.png");
}

/*virtual*/ CImage_Manager::~CImage_Manager()
{
	LOG("CImage_Manager Destructor\n");
}
