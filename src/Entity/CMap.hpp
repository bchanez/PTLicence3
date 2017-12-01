#ifndef CMAP_HPP_
#define CMAP_HPP_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <cctype>
#include <string>
#include "CDrawable.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

#define SIZE_TILE 40
#define SIZE_MAP_X 100
#define SIZE_MAP_Y 100

class CMap : public CDrawable
{
	public:

		explicit CMap();
		virtual ~CMap();

		void setTexture(void);

	protected:

	private:

};

#endif
