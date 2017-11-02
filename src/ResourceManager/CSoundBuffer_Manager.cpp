#include "CSoundBuffer_Manager.hpp"


/* explicit */ CSoundBuffer_Manager::CSoundBuffer_Manager(void)
: m_soundBuffers()
{
  std::cout << "CSoundBuffer_Manager constructor\n";
}

/* virtual */ CSoundBuffer_Manager::~CSoundBuffer_Manager (void)
{
  std::cout << "CSoundBuffer_Manager destructor\n";

  m_soundBuffers.clear();
}

const sf::SoundBuffer& CSoundBuffer_Manager::get_soundBuffer (const std::string& filename)
{
  // check if the sound already exist and return it
  for (std::map<std::string, sf::SoundBuffer>::iterator it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it)
    if (filename.compare(it->first) == 0)
      return it->second;

  // else add and return it (if sound is found)
  sf::SoundBuffer soundBuffer;
  for (std::vector<std::string>::iterator it = m_resourceDirectories.begin(); it != m_resourceDirectories.end(); ++it)
    if (soundBuffer.loadFromFile(*it + filename))
    {
      m_soundBuffers[filename] = soundBuffer;
      return m_soundBuffers[filename];
    }

  // else sound is not found
  return soundBuffer;
}

void CSoundBuffer_Manager::delete_soundBuffer (const sf::SoundBuffer& soundBuffer)
{
  // check if sound exist and delete it
  for (std::map<std::string, sf::SoundBuffer>::iterator it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it)
		if (&soundBuffer == &it->second)
		{
			m_soundBuffers.erase(it);
      return;
		}
}

void CSoundBuffer_Manager::delete_soundBuffer (const std::string& filename)
{
  // check if path of sound exist and delete it
  std::map<std::string, sf::SoundBuffer>::iterator it = m_soundBuffers.find(filename);
  if (it != m_soundBuffers.end())
    m_soundBuffers.erase(it);
}
