#ifndef CIMAGE_MANAGER_HPP_
#define CIMAGE_MANAGER_HPP_

class CImage_Manager : public CResource_Manager
{
  public:
    CImage_Manager();
    ~CImage_Manager();

  public:
    const sf::Image&	get_image     (const std::string& filename);
    void				      delete_image  (const sf::Image& image);
    void				      delete_image  (const std::string& filename);

  private:
    std::map<std::string, sf::Image> m_image;

};

#endif
