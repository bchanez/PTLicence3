#include "CDisplay.hpp"
#include <memory>
#include <iostream>

std::unique_ptr<sf::RenderWindow> m_window;

int m_zoom = 2;
std::unique_ptr<sf::View> m_view;

void CDisplay::init()
{
	//window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOWED_SCREEN_WIDTH, WINDOWED_SCREEN_HEIGHT), "Projet");
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Projet", sf::Style::Fullscreen);
	m_window.get()->setVerticalSyncEnabled(true);
	m_window.get()->setKeyRepeatEnabled(false);

	//Création de la vue du jeu
	m_view = std::make_unique<sf::View>();
	m_view.get()->setSize(1920.f/m_zoom, 1080.f/m_zoom);
	m_view.get()->setCenter(1920.f/m_zoom/2, 1080.f/m_zoom/2);
	m_window.get()->setView(* m_view.get());
}

void CDisplay::clear()
{
	m_window->clear();
}

void CDisplay::display()
{
	m_window->display();
}

void CDisplay::draw(const sf::Drawable & drawable)
{
	m_window->draw(drawable);
}

void CDisplay::draw(const sf::Drawable & drawable, const sf::Texture& texture)
{
	m_window->draw(drawable, &texture);
}

bool CDisplay::isOpen()
{
	return m_window->isOpen();
}

sf::RenderWindow * CDisplay::getWindow()
{
	return m_window.get();
}

sf::View * CDisplay::getView()
{
	return m_view.get();
}
