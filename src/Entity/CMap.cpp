#include "CMap.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cctype>
#include <string>

#define _TILE_SIZE 40

CMap::CMap()
{
  std::ifstream openfile("rsc/map/map.txt");
  sf::Texture tileTexture;  //Texture of the tile
  sf::Sprite tileSprite;    //Sprite of the tile

  sf::Vector2i map[100][100]; //Size of the map (Here 100 x 100)
  sf::Vector2i loadCounter = sf::Vector2i(0,-1); //loadCounter for the map

  int lastx = 0;

  if(openfile.is_open())
  {
      std::string tileLocation; //The first line in the Map.txt is the location of the texture file
      //openfile >> tileLocation; //We open the texture file

      //tileTexture.loadFromFile(tileLocation); //The texture is loaded

      tileSprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_TileMap_Grass)); //The sprite is set

      while(!openfile.eof())    //We browse the rest of the file
      {
          std::string str;
          openfile >> str;
          char x = str[0], y = str[2]; // Location of the desired tile in the texture file
          if(!isdigit(x) || !isdigit(y))
          {
              map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1); //If not valid
          } else {
              map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0'); // str to int (ASCII method)
          }

          if(openfile.peek() == '\n') //If we reach the end of a line
          {
              lastx = loadCounter.x;
              loadCounter.x = 0;
              loadCounter.y++;
          } else {
              loadCounter.x++;
          }
      }

  }

  m_prerender.create(4000, 4000);
  m_prerender.clear(sf::Color::Transparent);

  for (int i = 0; i <= lastx; ++i)
  {
      for (int j = 0; j <= loadCounter.y; ++j)
      {
          if(map[i][j].x != -1 && map[i][j].y != -1)
          {
              tileSprite.setPosition(i*40, j*40);
              tileSprite.setTextureRect(sf::IntRect(map[i][j].x * 40, map[i][j].y * 40, 40, 40));

              m_prerender.draw(tileSprite);

          }
      }
  }

  m_prerender.display();
  m_sprite.setTexture(m_prerender.getTexture());


}
