#ifndef CRESOURCE_MANAGER_HPP_
#define CRESOURCE_MANAGER_HPP_

#include <vector>
#include <iostream>

class CResource_Manager
{
  public:
    explicit  CResource_Manager        (void);
    virtual   ~CResource_Manager       (void);

  public:
    void      add_resourceDirectory    (const std::string& directory);
    void      remove_resourceDirectory (const std::string& directory);

  protected:
    std::vector<std::string> m_resourceDirectories;

};

#endif
