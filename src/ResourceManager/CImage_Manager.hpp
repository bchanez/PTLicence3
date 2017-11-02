#ifndef CIMAGE_MANAGER_HPP_
#define CIMAGE_MANAGER_HPP_

#include "CResource_Manager.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

class CImage_Manager : public CResource_Manager
{
  public:
    explicit          CImage_Manager  (void);
    virtual           ~CImage_Manager (void);

  public:
    const sf::Image&	get_image       (const std::string& filename);
    void				      delete_image    (const sf::Image& image);
    void				      delete_image    (const std::string& filename);

  private:
    std::map<std::string, sf::Image> m_images;

};

#endif
