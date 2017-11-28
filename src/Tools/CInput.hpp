#ifndef CINPUT_HPP_
#define CINPUT_HPP_

#include "SFML/Graphics.hpp"

class CInput
{

	struct Button { bool left, right, up, down, shift; };

public:

	explicit CInput();
	virtual ~CInput();

	Button	getButton(void) const;

	void setButton(int bouton, bool etat);

	void gestionInputs();
	void getInput();


private:

	Button button;

	//Enum pour les boutons
	enum { up, down, right, left, shift };
};
#endif
