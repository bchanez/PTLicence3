#include "CMap.hpp"

/*explicit*/ CMap::CMap()
{
  LOG("CMap Constructor\n");

  setTexture();
}

/*virtual*/ CMap::~CMap()
{
  LOG("CMap Destructor\n");
}

void CMap::genMap(void)
{
  //Codes
  //Coin HG 0.0
  //Bordure MG 0.1
  //Coin BG 0.2
  //Bordure MH 1.0
  //Full 1.1
  //Bordure MB 1.2
  //Coin HD 2.0
  //Bordure MD 2.1
  //Coin BD 2.2
  //Trou BD 3.0
  //Trou BG 5.0
  //Trou HD 3.3
  //Trou HG 5.3

  //Règles:
  //nB Trous >= 1 && < 3
  //nB Sorties = 4 (une par côté)
  //nB event => A decider

  std::string map_to_write[21][24];
  for (size_t i = 0; i < 21; i++) {
    for (size_t j = 0; j < 24; j++) {
      map_to_write[i][j] = "x,x";
    }
  }

  std::ofstream outfile ("rsc/map/test.txt");

  //Sorties
  int exit_up, exit_down, exit_right, exit_left;
  exit_up = CRandom::intInRange(0, 20);
  exit_right = CRandom::intInRange(0, 23);
  exit_down = CRandom::intInRange(0, 20);
  exit_left = CRandom::intInRange(0, 23);
  map_to_write[exit_up][0] = "1,1";
  map_to_write[exit_down][23] = "1,1";
  map_to_write[0][exit_right] = "1,1";
  map_to_write[20][exit_left] = "1,1";

  std::string line = "";
  outfile << "tiles.png" << std::endl;

  for (size_t i = 0; i < 21; i++) {
    line = "";

    for (size_t j = 0; j < 24; j++) {
      if(map_to_write[i][j] == "x,x"){
        if(i == 0){
          //Bordure gauche

          map_to_write[i][j] = "1,0";
        }
        else if(j == 0){
          //Bordure haut

          map_to_write[i][j] = "0,1";

          //Une sortie
        }
        else if(i == 20){
          //Bordure droite

          map_to_write[i][j] = "1,2";

        }else if(j == 23){
          //Bordure bas

          map_to_write[i][j] = "2,1";

          //Une sortie
        }
        else{
          //Coeur de la map

          map_to_write[i][j] = "1,1";

          //nbTrous
        }
      }
      if(j != 23){
        line = line + map_to_write[i][j] + " ";
      }else{
        line = line + map_to_write[i][j];
      }



    }

    outfile << line << std::endl;

  }




  outfile.close();
}

void CMap::setTexture(void)
{
  CMap::genMap();

  //std::ifstream openfile("rsc/map/map.txt");
  std::ifstream openfile("rsc/map/test.txt");
  sf::Texture tileTexture;  //Texture of the tile
  sf::Sprite tileSprite;    //Sprite of the tile

  sf::Vector2i map[SIZE_MAP_X][SIZE_MAP_Y]; //Size of the map (Here 100 x 100)
  sf::Vector2i loadCounter = sf::Vector2i(0,-1); //loadCounter for the map

  int lastx = 0;

  if(openfile.is_open())
  {
      std::string tileLocation; //The first line in the Map.txt is the location of the texture file

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

  m_prerender.create(SIZE_TILE * SIZE_MAP_X, SIZE_TILE * SIZE_MAP_Y);
  m_prerender.clear(sf::Color::Transparent);

  for (int i = 0; i <= lastx; ++i)
  {
      for (int j = 0; j <= loadCounter.y; ++j)
      {
          if(map[i][j].x != -1 && map[i][j].y != -1)
          {
              tileSprite.setPosition(i*SIZE_TILE, j*SIZE_TILE);
              tileSprite.setTextureRect(sf::IntRect(map[i][j].x * SIZE_TILE, map[i][j].y * SIZE_TILE, SIZE_TILE, SIZE_TILE));

              m_prerender.draw(tileSprite);

          }
      }
  }

  m_prerender.display();
  m_sprite.setTexture(m_prerender.getTexture());
}
