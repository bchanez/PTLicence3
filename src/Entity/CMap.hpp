#ifndef CMAP_HPP_
#define CMAP_HPP_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <cctype>
#include <string>
#include "CDrawable.hpp"
#include "../ResourceManager/CResourceHolder.hpp"
#include "../Tools/DEBUG.hpp"

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
