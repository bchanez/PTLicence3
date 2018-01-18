#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "Server/CServeur.hpp"
#include "CApplication.hpp"
#include "Tools/CRandom.hpp"

int main(int argc, char *argv[])
{

	bool choice = false;

  for (int i= 1; i < argc; ++i)
		for(unsigned int j = 0; j< strlen(argv[i]); ++j)
      switch(argv[i][j])
			{
				case 'r':
				{
					choice = true;
					break;
				}
				default:
					break;
			}

	CRandom::init();

	if (!choice)
	{
		CApplication game;
		game.runMainLoop();	// Lancement du jeu
	}
	else
	{
		CServeur serveur;
		serveur.initGame(100, 3);
		serveur.loopGame();
	}

	return EXIT_SUCCESS;
}
