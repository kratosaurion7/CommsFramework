#include "Graphical.h"

#include "PongBall.h"
#include "PongPaddle.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH  600

#define PADDLE_WIDTH 150
#define PADDLE_HEIGHT 30

#include "PackageFile.h"

int main()
{
	// TEst code start
	
	PackageFile* p = new PackageFile();
	p->AddFile("C:\\temp\\notnull.txt");
	p->Save("C:\\temp\\out.bin");

	return 0;

	// Below is game code
	BaseGraphicEngine* engine = new GraphicEngine();

	GraphicEngineInitParams* params = new GraphicEngineInitParams();
	params->EnableVerticalSync = true;
	params->WindowSize = new FSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	params->WindowTitle = new std::string("PONG");
	
	int PlayerOneScore = 0;
	int PlayerTwoScore = 0;

	engine->Initialize(params);

	BaseFont* gameFont = engine->CreateFont();
	gameFont->Load("Assets/arial.ttf");

	BaseText* playerOneScoreText = engine->CreateText();
	playerOneScoreText->SetFont(gameFont);
	playerOneScoreText->SetPos(0, 0);
	playerOneScoreText->SetCharacterSize(24);
	playerOneScoreText->SetColor(0xFFFFFFFF);
	playerOneScoreText->SetText(std::to_string(PlayerOneScore));

	engine->AddObject(playerOneScoreText);

	BaseSprite* paddleSpriteOne = engine->CreateSprite();
	BaseSprite* paddleSpriteTwo = engine->CreateSprite();

	BaseTexture* paddleTexture = engine->CreateTexture();
	paddleTexture->Initalize(PADDLE_WIDTH, PADDLE_HEIGHT);
	paddleTexture->SetSolidColor(0xFFEEDDFF);

	paddleSpriteOne->SetTexture(paddleTexture);
	paddleSpriteTwo->SetTexture(paddleTexture);

	paddleSpriteOne->SetPos(300, 20);
	paddleSpriteTwo->SetPos(300, 550);
	
	engine->AddObject(paddleSpriteOne);
	engine->AddObject(paddleSpriteTwo);

	PongPaddle* paddleOne = new PongPaddle(paddleSpriteOne);
	PongPaddle* paddleTwo= new PongPaddle(paddleSpriteTwo);

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
		if (engine->Keyboard->IsKeyPressed(D) && paddleSpriteOne->GetX() < WINDOW_WIDTH - PADDLE_WIDTH)
			paddleOne->Move(PADDLE_DIRECTION_RIGHT);
		
		if (engine->Keyboard->IsKeyPressed(A) && paddleSpriteOne->GetX() > 0)
			paddleOne->Move(PADDLE_DIRECTION_LEFT);

		if (engine->Keyboard->IsKeyPressed(Right) && paddleSpriteTwo->GetX() < WINDOW_WIDTH - PADDLE_WIDTH)
			paddleTwo->Move(PADDLE_DIRECTION_RIGHT);

		if (engine->Keyboard->IsKeyPressed(Left) && paddleSpriteTwo->GetX() > 0)
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
		if (ball->BallSprite->GetY() <= 0)
		{
			// P1 scores !
			PlayerOneScore++;
		}
		else if (ball->BallSprite->GetY() >= 0)
		{
			// P2 scores !
			PlayerTwoScore++;
		}

		// Unstuck check, if the ball is going in straight +1 or -1 X velocity.
		if (ball->Direction->X == -1 || ball->Direction->X == 1)
		{
			ball->Direction->X = (0.5 * ball->Direction->X);
		}

		playerOneScoreText->SetText(std::to_string(PlayerOneScore++));

		engine->Draw();
	}

	return 0;
}