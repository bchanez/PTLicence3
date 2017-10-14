#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(200, 200), "Projet");

    Texture texture;
    if (!texture.loadFromFile("rsc/img/dirt.png"))
    {
        cout << "Impossible d'ouvrir l'image : dirt.png";
    }

    Sprite sprite;
    sprite.setTexture(texture);

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
