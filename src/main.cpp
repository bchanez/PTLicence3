#include <SFML/Graphics.hpp>
#include "ResourceManager/CResourceHolder.hpp"
#include <iostream>
#include "CEntity.hpp"
#include "CCharacter.hpp"
using namespace std;
using namespace sf;

//Taille de la fenêtre de base
#define WINDOW_SIZE_X 1000
#define WINDOW_SIZE_Y 600

int main()
{
    //Création d'une fenêtre
    RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Projet");
    //Création de la vue du jeu
    View view(sf::FloatRect(-(WINDOW_SIZE_X/2), -(WINDOW_SIZE_Y/2), WINDOW_SIZE_X, WINDOW_SIZE_Y));
    window.setView(view);

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);


    //Nouveau personnage
    CCharacter character;

    //Boucle principale
    while (window.isOpen())
    {
        //Si un évènement est reçu
        sf::Event event;
        while (window.pollEvent(event))
        {
            //Si l'évènement est le clic sur la croix rouge pour fermer la fenêtre
            if (event.type == Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close(); //Fermeture de la fenêtre

            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }

            character.getEvent(event);
        }

        character.update();

        //Réinitialisation de l'affichage
        window.clear();
        //Chargement des images
        window.draw(character);
        //Affichage à l'écran
        window.display();
    }

    return 0;
}
