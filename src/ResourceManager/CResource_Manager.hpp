#ifndef CRESOURCE_MANAGER_HPP_
#define CRESOURCE_MANAGER_HPP_

class CResource_Manager
{
  public:
    CResource_Manager();
    ~CResource_Manager();

  public:
    void add_resourceDirectory    (const std::string& directory);
    void remove_resourceDirectory (const std::string& directory);

  protected:
    std::vector<std::string> m_resourceDirectories;

};

#endif
