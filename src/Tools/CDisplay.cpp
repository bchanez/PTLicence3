#include "CDisplay.hpp"
#include <memory>
#include <iostream>

std::unique_ptr<sf::RenderWindow> window;

void CDisplay::init()
{
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOWED_SCREEN_WIDTH, WINDOWED_SCREEN_HEIGHT, 32), "Jeu");
	window.get()->setVerticalSyncEnabled(true);
	window.get()->setKeyRepeatEnabled(true);
}

void CDisplay::clear()
{
	window->clear();
}

void CDisplay::display()
{
	window->display();
}

void CDisplay::draw(const sf::Drawable & drawable)
{
	window->draw(drawable);
}

void CDisplay::draw(const sf::Drawable & drawable, const sf::Texture& texture)
{
	window->draw(drawable, &texture);
}

// Gère les évenements pour la fenêtre uniquement
void CDisplay::checkWindowEvents()
{
	sf::Event m_event;
	while (window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			window->close();
	}
}

bool CDisplay::isOpen()
{
	return window->isOpen();
}
