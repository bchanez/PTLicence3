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

}

void CResource_Manager::remove_resourceDirectory (const std::string& directory)
{

}
