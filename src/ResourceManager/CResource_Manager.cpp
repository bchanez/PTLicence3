#include "CResource_Manager.hpp"


/* explicit */ CResource_Manager::CResource_Manager (void)
: m_resourceDirectories()
{
  std::cout << "CResource_Manager constructor\n";
}

/* virtual */ CResource_Manager::~CResource_Manager (void)
{
  std::cout << "CResource_Manager destructor\n";

  m_resourceDirectories.clear();
}

void CResource_Manager::add_resourceDirectory (const std::string& directory)
{
  // check if the directory already exist else add it
  for (std::vector<std::string>::iterator it = m_resourceDirectories.begin(); it != m_resourceDirectories.end(); ++it)
    if (directory.compare(*it) == 0)
      return;

  // add the directory
  m_resourceDirectories.push_back(directory);
}

void CResource_Manager::remove_resourceDirectory (const std::string& directory)
{
  // check if the directory exist and delete it
  for (std::vector<std::string>::iterator it = m_resourceDirectories.begin(); it != m_resourceDirectories.end(); ++it)
    if (directory.compare(*it) == 0)
    {
      // delete the directory
      m_resourceDirectories.erase(it);
      return;
    }
}
