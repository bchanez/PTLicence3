#ifndef CMUSIC_MANAGER_HPP_
#define CMUSIC_MANAGER_HPP_

#include "CResource_Manager.hpp"
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>

class CMusic_Manager : public CResource_Manager
{
  public:
    explicit          CMusic_Manager  (void);
    virtual           ~CMusic_Manager (void);

  public:
    const sf::Music&	get_music       (const std::string& filename);
    void				      delete_music    (const sf::Music& music);
    void				      delete_music    (const std::string& filename);

  private:
    std::map<std::string, sf::Music> m_music;

};

#endif
