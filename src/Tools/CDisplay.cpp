#include "CDisplay.hpp"
#include <memory>
#include <iostream>

std::unique_ptr<sf::RenderWindow> window;
int m_zoom = 2;
sf::View m_view;

void CDisplay::init()
{
	//window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOWED_SCREEN_WIDTH, WINDOWED_SCREEN_HEIGHT), "Projet");
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Projet", sf::Style::Fullscreen);
	window.get()->setVerticalSyncEnabled(true);
	window.get()->setKeyRepeatEnabled(false);

	//Création de la vue du jeu
	m_view.setSize(1920.f/m_zoom, 1080.f/m_zoom);
	m_view.setCenter(1920.f/m_zoom/2, 1080.f/m_zoom/2);
	window.get()->setView(m_view);
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
		if (m_event.type == sf::Event::Closed
			|| (m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::Escape))
				window->close();
	}
}

bool CDisplay::isOpen()
{
	return window->isOpen();
}
