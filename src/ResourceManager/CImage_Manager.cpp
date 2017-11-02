#include "CImage_Manager.hpp"


/* explicit */ CImage_Manager::CImage_Manager (void)
: m_images()
{
  std::cout << "CImage_Manager constructor\n";
}

/* virtual */ CImage_Manager::~CImage_Manager (void)
{
  std::cout << "CImage_Manager destructor\n";

  m_images.clear();
}

const sf::Image& CImage_Manager::get_image (const std::string& filename)
{
  // check if the image already exist and return it
  for (std::map<std::string, sf::Image>::iterator it = m_images.begin(); it != m_images.end(); ++it)
    if (filename.compare(it->first) == 0)
      return it->second;

  // else add and return it (if image is found)
  sf::Image image;
  for (std::vector<std::string>::iterator it = m_resourceDirectories.begin(); it != m_resourceDirectories.end(); ++it)
    if (image.loadFromFile(*it + filename))
    {
      m_images[filename] = image;
      return m_images[filename];
    }

  // else image is not found
  return image;
}

void CImage_Manager::delete_image (const sf::Image& image)
{
  // check if image exist and delete it
  for (std::map<std::string, sf::Image>::iterator it = m_images.begin(); it != m_images.end(); ++it)
		if (&image == &it->second)
		{
			m_images.erase(it);
      return;
		}
}

void CImage_Manager::delete_image (const std::string& filename)
{
  // check if path of image exist and delete it
  std::map<std::string, sf::Image>::iterator it = m_images.find(filename);
  if (it != m_images.end())
    m_images.erase(it);
}
