#ifndef CDISPLAY_HPP_
#define CDISPLAY_HPP_

#include "SFML/Graphics.hpp"

namespace CDisplay
{
	void init();

	void clear();
	void display();

	void draw(const sf::Drawable& drawable);
	void draw(const sf::Drawable& drawable, const sf::Texture& texture);

	void checkWindowEvents();

	bool isOpen();

	// Taille de la fenetre en WINDOWED : 800x480 pixels
	constexpr int WINDOWED_SCREEN_WIDTH = 800;
	constexpr int WINDOWED_SCREEN_HEIGHT = 480;
}

#endif