#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "CDisplay.hpp"
#include "DEBUG.hpp"

class CInput
{

	struct Button { bool left, right, up, down, shift; };

public:

	explicit CInput();
	virtual ~CInput();

	Button	getButton(void) const;

	void setButton(int bouton, bool etat);

	void gestionInputs(sf::Event * event);
	void getInput(sf::Event * event);


private:

	Button button;

	//Enum pour les boutons
	enum { up, down, right, left, shift };
};
