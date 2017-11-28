#include "CApplication.hpp"
#include "Tools/CRandom.hpp"

int main()
{
	CRandom::init();

	CApplication game;
	game.runMainLoop();	// Lancement du jeu

	return EXIT_SUCCESS;
}
