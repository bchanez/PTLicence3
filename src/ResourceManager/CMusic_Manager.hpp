#ifndef CMUSIC_MANAGER_HPP_
#define CMUSIC_MANAGER_HPP_

class CMusic_Manager : public CResource_Manager
{
  public:
    CMusic_Manager();
    ~CMusic_Manager();

  public:
    const sf::Music&	get_music     (const std::string& filename);
    void				      delete_music  (const sf::Music& music);
    void				      delete_music  (const std::string& filename);

  private:
    std::map<std::string, sf::Music> m_music;

};

#endif
