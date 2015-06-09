#include <SFML/Graphics.hpp>

#include "Graphic\DSprite.h";

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML works!");

    window.setVerticalSyncEnabled(true);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Texture tex;
    tex.loadFromFile("Assets/texture.png");

    sf::Sprite spr;
    spr.setTexture(tex);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(shape);
        window.draw(spr);
        window.display();
    }

    return 0;
}