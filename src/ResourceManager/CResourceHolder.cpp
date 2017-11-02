#include "CResourceHolder.hpp"

CResourceHolder::CResourceHolder()
{
}

CResourceHolder::~CResourceHolder()
{
}

const CResourceHolder & CResourceHolder::get()
{
	static CResourceHolder holder;
	return holder;
}

const sf::Texture & CResourceHolder::getTexture(ETexture_Name name) const
{
	return m_textures.get(name);
}

const sf::Font & CResourceHolder::getFont(EFont_Name name) const
{
	return m_fonts.get(name);
}

const sf::SoundBuffer & CResourceHolder::getSound(ESound_Name name) const
{
	return m_sounds.get(name);
}
