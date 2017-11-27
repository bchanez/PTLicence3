#include "CInput.hpp"
#include <iostream>
#include "DEBUG.hpp"

CInput::CInput()
{
  LOG("CInput Constructor\n");

	button.left = button.right = button.up = button.down = button.shift = false;
}

CInput::~CInput()
{
  LOG("CInput Destructor\n");
}

CInput::Button CInput::getButton(void) const
{
	return button;
}

void CInput::setButton(int bouton, bool etat)
{
	switch (bouton)
	{
		case up:
		button.up = etat;
		break;

		case down:
		button.down = etat;
		break;

		case right:
		button.right = etat;
		break;

		case left:
		button.left = etat;
		break;

		case shift:
		button.shift = etat;
		break;
	}
}

//Fonctions
void CInput::gestionInputs()
{
	// gère le clavier
	getInput();

	// gere la souris
}

// Gère les input clavier du CCharacter uniquement
void CInput::getInput()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)
	)
		button.up = true;
	else
		button.up = false;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::A)
	)
		button.left = true;
	else
		button.left = false;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		button.down = true;
	else
		button.down = false;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		button.right = true;
	else
		button.right = false;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		button.shift = true;
	else
		button.shift = false;
}
