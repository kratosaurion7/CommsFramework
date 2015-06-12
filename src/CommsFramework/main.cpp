#include <SFML/Graphics.hpp>

#include "DSprite.h"

#include "GraphicEngine.h"

#include "FileReader.h"

#include "BaseGraphicEngine.h"

#include <string>

int main()
{
	BaseGraphicEngine* eng = new GraphicEngine();

	GraphicEngineInitParams* params = new GraphicEngineInitParams();
	params->EnableVerticalSync = true;
	params->WindowSize = new FSize(600, 600);
	params->WindowTitle = new std::string("WINNING!");

	eng->Initialize(params);

	BaseSprite* spr = eng->CreateSprite();

	BaseTexture* txr = eng->CreateTexture();
	txr->Load("Assets/Texture.png");
	spr->SetTexture(txr);
	spr->Show(true);

	eng->AddObject(spr);
	

	eng->StartLooping();

	return 0;
}

int main3()
{
	getchar();

	for (int i = 0; i < 100000;i++)
	{
		FileReader* rdr = new FileReader();

		rdr->OpenFile("input.txt", READ);

		FileContents* contents = rdr->GetFileContents();

		delete rdr;
		delete contents;
	}

	getchar();

	return 0;
}

int main2()
{
    sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML works!");

    window.setVerticalSyncEnabled(true);


	DSprite* mySprite = new DSprite();


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