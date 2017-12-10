#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <cstdlib>
#include "CDrawable.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"
#include "../Tools/CRandom.hpp"

#define SIZE_TILE 40
#define SIZE_MAP_X 100
#define SIZE_MAP_Y 100

class CMap : public CDrawable
{
	public:

		explicit CMap();
		virtual ~CMap();

		void setTexture(void) override;
		void genMap(void);

	protected:

	private:

};
