
#include "Graphical.h"

#include "BaseSprite.h"
#include "DTexture.h"

#include "FPosition.h"
#include "FRectangle.h"

#include "PongBall.h"
#include "PongPaddle.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH  600

#define PADDLE_WIDTH 150
#define PADDLE_HEIGHT 30

int main()
{
	BaseGraphicEngine* engine = new GraphicEngine();

	GraphicEngineInitParams* params = new GraphicEngineInitParams();
	params->EnableVerticalSync = true;
	params->WindowSize = new FSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	params->WindowTitle = new std::string("PONG");
	
	engine->Initialize(params);

	BaseSprite* paddle1 = engine->CreateSprite();
	BaseSprite* paddle2 = engine->CreateSprite();

	BaseTexture* paddleTexture = engine->CreateTexture();
	paddleTexture->Initalize(PADDLE_WIDTH, PADDLE_HEIGHT);
	paddleTexture->SetSolidColor(0xFFEEDDFF);

	paddle1->SetTexture(paddleTexture);
	paddle2->SetTexture(paddleTexture);

	paddle1->SetPos(300, 20);
	paddle2->SetPos(300, 550);
	
	engine->AddObject(paddle1);
	engine->AddObject(paddle2);

	PongPaddle* paddleOne = new PongPaddle(paddle1);
	PongPaddle* paddleTwo= new PongPaddle(paddle2);

	paddleOne->Velocity->Set(5, 0);
	paddleTwo->Velocity->Set(5, 0);

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
		
		// Check for game exit
		if (engine->Keyboard->IsKeyPressed(Escape))
			engine->Stop();
		
		// Check for player paddles movements
		if (engine->Keyboard->IsKeyPressed(D) && paddle1->GetX() < WINDOW_WIDTH - PADDLE_WIDTH)
			paddleOne->Move(PADDLE_DIRECTION_RIGHT);
		
		if (engine->Keyboard->IsKeyPressed(A) && paddle1->GetX() > 0)
			paddleOne->Move(PADDLE_DIRECTION_LEFT);

		if (engine->Keyboard->IsKeyPressed(Right) && paddle2->GetX() < WINDOW_WIDTH - PADDLE_WIDTH)
			paddleTwo->Move(PADDLE_DIRECTION_RIGHT);

		if (engine->Keyboard->IsKeyPressed(Left) && paddle2->GetX() > 0)
			paddleTwo->Move(PADDLE_DIRECTION_LEFT);

		// Check for ball collision with the paddles.
		FRectangle* p1CollisionBox = paddleOne->PaddleSprite->GetRectangle();
		FRectangle* p2CollisionBox = paddleTwo->PaddleSprite->GetRectangle();
		FRectangle* ballCollisionBox = ball->BallSprite->GetRectangle();

		if (p1CollisionBox->Intersect(ballCollisionBox))
		{
			// Simple collision for now
			ball->Direction->Y *= -1;
		}
		else if (p2CollisionBox->Intersect(ballCollisionBox))
		{
			ball->Direction->Y *= -1;
		}

		delete(p1CollisionBox);
		delete(p2CollisionBox);
		delete(ballCollisionBox);

		// Check if the ball touches the top or bottom for points

		engine->Draw();
	}

	return 0;
}