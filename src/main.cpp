#include <SFML/Graphics.hpp>
#include "ResourceManager/CResourceHolder.hpp"
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(200, 200), "Projet");

<<<<<<< HEAD
    Texture texture;
    if (!texture.loadFromFile("rsc/graphics/character.png"))
    {
        cout << "Impossible d'ouvrir l'image : character.png";
    }

=======
>>>>>>> e667c25615f1a0d059a45d63410953f48df2b306
    Sprite sprite;
    sprite.setTexture(CResourceHolder::get().texture(ETexture_Name::e_Characters));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
