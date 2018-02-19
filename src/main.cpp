#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "Server/CServer.hpp"
#include "CApplication.hpp"
#include "Tools/CRandom.hpp"
#include "CConfig.hpp"
#include <exception>

//ARG=r => Serveur
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

	//Seed du random
	CRandom::init();

	if (!choice)
	{
		CApplication game;
		game.runMainLoop();	// Lancement du jeu

	}
	else
	{
		CServer server;
		server.loopServer();
	}

	return EXIT_SUCCESS;
}
