#ifndef CSOUND_MANAGER_HPP_
#define CSOUND_MANAGER_HPP_

class CSound_Manager : public CResource_Manager
{
  public:
    CSound_Manager();
    ~CSound_Manager();

  public:
    const sf::Sound&	get_sound     (const std::string& filename);
    void				      delete_sound  (const sf::Sound& sound);
    void				      delete_sound  (const std::string& filename);

  private:
    std::map<std::string, sf::Sound> m_sound;

};

#endif
