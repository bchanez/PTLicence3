#include <SFML/Graphics.hpp>
#include "ResourceManager/CResourceHolder.hpp"
#include <iostream>
#include "Entity/CEntity.hpp"
#include "Entity/CCharacter.hpp"
#include "Entity/CPNJ.hpp"
#include "Entity/CMap.hpp"
using namespace std;
using namespace sf;

//Taille de la fenêtre de base
#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600

#define PNJ_NB 100

int main()
{

    srand(time(NULL));

    float ZOOM = 2;   //Pour un meilleur affichage, le multiplicateur doit être un chiffre rond ou 1.5

    //Création d'une fenêtre
    //RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Projet", sf::Style::Fullscreen);
    RenderWindow window(VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Projet", sf::Style::Fullscreen);
    //Création de la vue du jeu
    View view(sf::FloatRect(0, 0, 1920/ZOOM, 1080/ZOOM));
    view.setCenter(0, 0);
    window.setView(view);
    //Options de la fenêtre
    window.setFramerateLimit(70);
    window.setKeyRepeatEnabled(false);


    //Nouveau personnage
    CCharacter character;

    //Nouveau PNJs
    CPNJ pnj[PNJ_NB];

    //Nouvelle Map
    CMap map;

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

            //Adapte l'affichage à la taille de la fenêtre
            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width/ZOOM, event.size.height/ZOOM);
                window.setView(view);
            }

            character.getEvent(event);
        }

        //Mise à jour du personnage
        character.update();

        //Mise à jour du personnage
        for (int i=0; i<PNJ_NB; i++)
          pnj[i].update();

        //Réinitialisation de l'affichage
        window.clear();
        //Chargement des images
        window.draw(map);

        window.draw(character);
        for (int i=0; i<PNJ_NB; i++)
          window.draw(pnj[i]);
        //Affichage à l'écran
        window.display();
    }

    return 0;
}
