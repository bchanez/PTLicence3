#ifndef CSOUND_MANAGER_HPP_
#define CSOUND_MANAGER_HPP_

#include "SFML/Audio.hpp"
#include <map>
#include "CResourceManager.hpp"

enum class ESound_Name
{
};

class CSound_Manager : public CResourceManager<ESound_Name, sf::SoundBuffer>
{
	public:
		explicit CSound_Manager();
		virtual ~CSound_Manager();

	private:
		std::map <ESound_Name, sf::SoundBuffer> m_sounds;

};

#endif
