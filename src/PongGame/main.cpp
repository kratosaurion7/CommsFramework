
#include "Graphical.h"

int main()
{
	BaseGraphicEngine* engine = new GraphicEngine();

	GraphicEngineInitParams* params = new GraphicEngineInitParams();
	params->EnableVerticalSync = true;
	params->WindowSize = new FSize(600, 600);
	params->WindowTitle = new std::string("PONG");

	engine->Initialize(params);

	BaseSprite* paddle1 = engine->CreateSprite();
	BaseSprite* paddle2 = engine->CreateSprite();

	BaseTexture* paddleTexture = engine->CreateTexture();
	paddleTexture->Initalize(150, 30);
	paddleTexture->SetSolidColor(0xFFEEDDCC);

	paddle1->SetTexture(paddleTexture);
	paddle2->SetTexture(paddleTexture);

	paddle1->SetPos(300, 20);
	paddle2->SetPos(300, 550);
	
	engine->AddObject(paddle1);
	engine->AddObject(paddle2);

	engine->StartLooping();


}