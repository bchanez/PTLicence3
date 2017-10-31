#ifndef CFONT_MANAGER_HPP_
#define CFONT_MANAGER_HPP_

class CFont_Manager : public CResource_Manager
{
  public:
    CFont_Manager();
    ~CFont_Manager();

  public:
    const sf::Font&	  get_font     (const std::string& filename);
    void				      delete_font  (const sf::Font& font);
    void				      delete_font  (const std::string& filename);

  private:
    std::map<std::string, sf::Font> m_font;

};

#endif
