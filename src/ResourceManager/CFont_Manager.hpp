#ifndef CFONT_MANAGER_HPP_
#define CFONT_MANAGER_HPP_

#include "CResource_Manager.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

class CFont_Manager : public CResource_Manager
{
  public:
    explicit          CFont_Manager   (void);
    virtual           ~CFont_Manager  (void);

  public:
    const sf::Font&	  get_font        (const std::string& filename);
    void				      delete_font     (const sf::Font& font);
    void				      delete_font     (const std::string& filename);

  private:
    std::map<std::string, sf::Font> m_fonts;

};

#endif
