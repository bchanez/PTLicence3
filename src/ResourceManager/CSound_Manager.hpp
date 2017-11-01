#ifndef CSOUND_MANAGER_HPP_
#define CSOUND_MANAGER_HPP_

#include "CResource_Manager.hpp"
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>

class CSound_Manager : public CResource_Manager
{
  public:
    explicit          CSound_Manager  (void);
    virtual           ~CSound_Manager (void);

  public:
    const sf::Sound&	get_sound       (const std::string& filename);
    void				      delete_sound    (const sf::Sound& sound);
    void				      delete_sound    (const std::string& filename);

  private:
    std::map<std::string, sf::Sound> m_sound;

};

#endif
