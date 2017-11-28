#ifndef CRESOURCE_HOLDER_HPP_
#define CRESOURCE_HOLDER_HPP_

#include "CTexture_Manager.hpp"
#include "CFont_Manager.hpp"
#include "CSound_Manager.hpp"

class CResourceHolder
{
	public:
		explicit CResourceHolder();
		virtual ~CResourceHolder();

		static const CResourceHolder& get();

		const sf::Texture& texture(ETexture_Name name) const;
		const sf::Font& font(EFont_Name name) const;
		const sf::SoundBuffer& sound(ESound_Name name) const;

	private:
		CTexture_Manager m_textures;
		CFont_Manager m_fonts;
		CSound_Manager m_sounds;
};

#endif
