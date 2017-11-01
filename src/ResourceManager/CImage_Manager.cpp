#include "CImage_Manager.hpp"


/* explicit */ CImage_Manager::CImage_Manager (void)
: m_image()
{
  std::cout << "CImage_Manager constructor\n";
}

/* virtual */ CImage_Manager::~CImage_Manager (void)
{
  std::cout << "CImage_Manager destructor\n";

  m_image.clear();
}

const sf::Image& CImage_Manager::get_image (const std::string& filename)
{
  sf::Image image;
  return image;
}

void CImage_Manager::delete_image (const sf::Image& image)
{

}

void CImage_Manager::delete_image (const std::string& filename)
{

}
