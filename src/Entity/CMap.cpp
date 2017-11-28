#include "CMap.hpp"
#include "../Tools/DEBUG.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cctype>
#include <string>

/*explicit*/ CMap::CMap()
{
  LOG("CMap Constructor\n");
}

/*virtual*/ CMap::~CMap()
{
  LOG("CMap Destructor\n");
}
