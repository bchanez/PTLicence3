#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "CResourceManager.hpp"
#include "../Tools/DEBUG.hpp"


enum class EImage_Name
{
	e_Hair_1,
	e_Hair_2,
	e_Hair_3,
	e_Hair_4,
	e_Hair_5,
	e_Hair_6,
	e_Hair_7,
	e_Hair_8,
};

class CImage_Manager : public CResourceManager<EImage_Name, sf::Image>
{
	public:
		explicit CImage_Manager();
		virtual ~CImage_Manager();

	private:
		std::map <EImage_Name, sf::Image> m_images;

};
