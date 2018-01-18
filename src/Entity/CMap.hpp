#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "../Tools/CDrawable.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CRandom.hpp"
#include "../StateEngine/CConfig.hpp"

class CMap : public CDrawable
{
	public:

		explicit CMap();
		virtual ~CMap();

		void setTexture(void);
		void genMap(void);
		void genHole(int x, int y);
		void writeMapFile(void);
		void writeCollisionFile(void);

		std::string game_map[SIZE_MAP_X][SIZE_MAP_Y];
		sf::Vector2i map[SIZE_MAP_X][SIZE_MAP_Y];

	protected:

	private:

};
