
#include "Graphical.h"

#include "PongBall.h"
#include "PongPaddle.h"

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
	paddleTexture->SetSolidColor(0xFFEEDDFF);

	paddle1->SetTexture(paddleTexture);
	paddle2->SetTexture(paddleTexture);

	paddle1->SetPos(300, 20);
	paddle2->SetPos(300, 550);
	
	engine->AddObject(paddle1);
	engine->AddObject(paddle2);

	PongPaddle* paddleOne = new PongPaddle(paddle1);

	BaseSprite* ballSprite = engine->CreateSprite();
	BaseTexture* ballTexture = engine->CreateTexture();
	ballTexture->Initalize(25, 25);
	ballTexture->SetSolidColor(0xFFFFFFFF);

	ballSprite->SetTexture(ballTexture);

	PongBall* ball = new PongBall(ballSprite);
	ball->SetupBounds(0, 0, 600, 600);
	ball->ResetBallPosition();

	engine->AddObject(ball->BallSprite);

	ball->Direction->Set(1, 0);
	ball->Velocity->Set(3, 3);

	engine->Start();

	while (engine->IsRunning())
	{
		engine->ProcessEvents();

		ball->Update();
		
		if (engine->Keyboard->IsKeyPressed(Escape))
			engine->Stop();
		
		if (engine->Keyboard->IsKeyPressed(D))
			paddle1->IncrementX(5);
		
		if (engine->Keyboard->IsKeyPressed(A))
			paddle1->IncrementX(-5);

		if (engine->Keyboard->IsKeyPressed(Right))
			paddle2->IncrementX(5);

		if (engine->Keyboard->IsKeyPressed(Left))
			paddle2->IncrementX(-5);

		engine->Draw();
	}

	return 0;
}