#ifndef CMAP_HPP_
#define CMAP_HPP_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
		void genMap(void);
		int rand_a_b(int a, int b);

	protected:

	private:

};

#endif
