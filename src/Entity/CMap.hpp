#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <cstdlib>
#include "../Tools/CDrawable.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CRandom.hpp"

#define SIZE_TILE 40
#define SIZE_MAP_X 50
#define SIZE_MAP_Y 50

class CMap : public CDrawable
{
	public:

		explicit CMap();
		virtual ~CMap();

		void setTexture(void);
		void genMap(void);
		void genHole(int x, int y, std::string map_to_write[SIZE_MAP_X][SIZE_MAP_Y]);

	protected:

	private:

};
