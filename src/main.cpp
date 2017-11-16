#include <SFML/Graphics.hpp>
#include "ResourceManager/CResourceHolder.hpp"
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(200, 200), "Projet");

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
