#include "CMap.hpp"

//Explicit
CMap::CMap()
{
  LOG("CMap Constructor\n");

  setTexture();
}

//Virtual
CMap::~CMap()
{
  LOG("CMap Destructor\n");
}

//Generation of holes *WIP*
//TO DO : More types of holes
void CMap::genHole(int i, int j)
{
  CMap::map[i][j] = sf::Vector2i(5,2);
  CMap::map[i][j+1] = sf::Vector2i(5,0);

  CMap::map[i+1][j] = sf::Vector2i(3,2);
  CMap::map[i+1][j+1] = sf::Vector2i(3,0);
}

//Generation of the map
void CMap::genMap(void)
{
  int nb_Holes = 10;

  //Initializing the map
  for (size_t i = 0; i < SIZE_MAP_X; i++)
  {
    for (size_t j = 0; j < SIZE_MAP_Y; j++)
    {
      CMap::map[i][j] = sf::Vector2i(-1, -1);
    }
  }


  //Exits
  int exit_up, exit_down, exit_right, exit_left;
  exit_up = CRandom::intInRange(0, SIZE_MAP_X);
  exit_right = CRandom::intInRange(0, SIZE_MAP_Y);
  exit_down = CRandom::intInRange(0, SIZE_MAP_X);
  exit_left = CRandom::intInRange(0, SIZE_MAP_Y);
  CMap::map[exit_up][0] = sf::Vector2i(1, 1);
  CMap::map[exit_down][SIZE_MAP_Y-1] = sf::Vector2i(1, 1);
  CMap::map[0][exit_right] = sf::Vector2i(1, 1);
  CMap::map[SIZE_MAP_X-1][exit_left] = sf::Vector2i(1, 1);


  //Corners
  CMap::map[0][0] = sf::Vector2i(0, 0);
  CMap::map[SIZE_MAP_X-1][0] = sf::Vector2i(2, 0);
  CMap::map[0][SIZE_MAP_Y-1] = sf::Vector2i(0, 2);
  CMap::map[SIZE_MAP_X-1][SIZE_MAP_Y-1]= sf::Vector2i(2, 2);


  //Borders and Core of the map
  for (size_t i = 0; i < SIZE_MAP_X; i++)
  {
    for (size_t j = 0; j < SIZE_MAP_Y; j++)
    {
      //Check if the texture is not set yet
      if(CMap::map[i][j].x == -1 && CMap::map[i][j].y == -1)
      {
        //Left Border
        if(i == 0)
        {
          CMap::map[i][j] = sf::Vector2i(0, 1);
        }

        //Up Border
        else if(j == 0)
        {
          CMap::map[i][j] = sf::Vector2i(1, 0);
        }

        //Right Border
        else if(i == SIZE_MAP_X - 1)
        {
          CMap::map[i][j] = sf::Vector2i(2, 1);
        }

        //Down Border
        else if(j == SIZE_MAP_Y - 1)
        {
          CMap::map[i][j] = sf::Vector2i(1, 2);
        }

        //Core of the map
        else
        {
          CMap::map[i][j] = sf::Vector2i(1, 1);

          if(i > 0 && i < SIZE_MAP_X -1 && j > 0 && j < SIZE_MAP_Y - 1)
          {
            //Holes

            //First point of the holes
            if (nb_Holes > 0 && i < SIZE_MAP_X - 3 && j < SIZE_MAP_Y -3 && i > 3 && j > 3)
            {
              if(CRandom::intInRange(0, 150) == 1)
              {
                CMap::genHole(i, j);
                nb_Holes -= 1;
              }
            }
          }
        }
      }
    }
  }
}

void CMap::writeMapFile()
{
  std::ofstream myfile;
  myfile.open("rsc/Map/map.txt");
  myfile << SIZE_MAP_X << " " << SIZE_MAP_Y << '\n';
  for (int i = 0; i< SIZE_MAP_X; ++i)
  {
    for (int j = 0; j <= SIZE_MAP_Y; ++j)
    {
      myfile << CMap::map[i][j].x << ',' << CMap::map[i][j].y << ' ';
    }
    myfile << '\n';
  }
  myfile.close();
}

void CMap::writeCollisionFile()
{
  std::ofstream myfile;
  myfile.open("rsc/Map/colmap.txt");

  myfile.close();
}


// Setting textures
void CMap::setTexture(void)
{
  CMap::genMap();
  CMap::writeMapFile();

  sf::Texture tileTexture;  //Texture of the tile
  sf::Sprite tileSprite;    //Sprite of the tile

  m_prerender.create(SIZE_TILE * SIZE_MAP_X, SIZE_TILE * SIZE_MAP_Y);
  m_prerender.clear(sf::Color::Transparent);

  tileSprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_TileMap_Grass)); //The sprite is set

  for (int i = 0; i < SIZE_MAP_X; ++i)
  {
      for (int j = 0; j <= SIZE_MAP_Y; ++j)
      {
        if(CMap::map[i][j].x != -1 && CMap::map[i][j].y != -1)
        {
            tileSprite.setPosition(i*SIZE_TILE, j*SIZE_TILE);
            tileSprite.setTextureRect(sf::IntRect(CMap::map[i][j].x * SIZE_TILE, CMap::map[i][j].y * SIZE_TILE, SIZE_TILE, SIZE_TILE));

            m_prerender.draw(tileSprite);
        }
      }
  }

  //PLANTING FLOWERS
  tileSprite.setTextureRect(sf::IntRect(4 * SIZE_TILE, 1 * SIZE_TILE, SIZE_TILE, SIZE_TILE));
  tileSprite.setScale(sf::Vector2f(0.5f, 0.5f));

  for (int i = 0; i < SIZE_MAP_X*SIZE_MAP_Y/2; i++){
    tileSprite.setPosition(sf::Vector2f(CRandom::intInRange(SIZE_TILE, SIZE_TILE+((((SIZE_MAP_X-2)*SIZE_TILE)/2)*2)),
                                        CRandom::intInRange(SIZE_TILE, SIZE_TILE+((((SIZE_MAP_Y-2)*SIZE_TILE)/2)*2))));
    //tileSprite.setPosition(sf::Vector2f(i, i));
    m_prerender.draw(tileSprite);
  }

  m_prerender.display();
  m_sprite.setTexture(m_prerender.getTexture());
}
