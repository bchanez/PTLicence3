#ifndef CSOUND_MANAGER_HPP_
#define CSOUND_MANAGER_HPP_

#include "CResource_Manager.hpp"
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>

class CSoundBuffer_Manager : public CResource_Manager
{
  public:
    explicit                CSoundBuffer_Manager  (void);
    virtual                 ~CSoundBuffer_Manager (void);

  public:
    const sf::SoundBuffer&	get_soundBuffer       (const std::string& filename);
    void				            delete_soundBuffer    (const sf::SoundBuffer& soundBuffer);
    void			              delete_soundBuffer    (const std::string& filename);

  private:
    std::map<std::string, sf::SoundBuffer> m_soundBuffers;

};

#endif
