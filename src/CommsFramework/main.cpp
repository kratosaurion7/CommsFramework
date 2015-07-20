#include <SFML/Graphics.hpp>

#include "DSprite.h"
#include "DTexture.h"
#include "SFMLFont.h"
#include "SFMLKeyboard.h"
#include "SFMLText.h"

#include "GraphicEngine.h"

#include "FileReader.h"

#include "BaseGraphicEngine.h"

#include "PackageFile.h"

#include <string>

#include <memory>

using namespace std;

struct Tard
{
	char* arr;
	int two;

	~Tard()
	{
		delete arr;
	};
};

struct Qwerty
{
	Tard* trd;
};

int main4();

int main()
{
	PackageFile* fil = new PackageFile();
	
	fil->AddFile("E:\\Temp\\tex.txt");

	fil->Save("E:\\Temp\\out.pack");

	int(*testes)();
	testes = &main4;

	std::vector<int> vec;

	vec.push_back(9);
	vec.push_back(8);
	vec.push_back(7);
	vec.push_back(6);

	vec.insert(vec.begin() + 2, 4);

	auto element = std::find_if(vec.begin(), vec.end(), [](const int n) { return n == 8;});

	auto it = vec.begin();

	while (it != vec.end())
	{
		printf("%d", *it);

		it++;
	}

	{
		Tard* newTard = new Tard();
		newTard->arr = new char[1024 * 1024 * 8 * 8];

		unique_ptr<Tard> blerb(newTard);
		//blerb->arr = new char[1024 * 1024 * 8 * 8];
		blerb->two = 888;
		
		auto x = make_unique<Tard*>(new Tard);

	}
	int i = 0;

	return 0;
}


int main4()
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

	eng->Start();

	return 0;
}

int main3()
{
	getchar();

	for (int i = 0; i < 100000;i++)
	{
		FileReader* rdr = new FileReader();

		rdr->OpenFile("input.txt");

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