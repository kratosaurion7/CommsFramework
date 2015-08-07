#include "Graphical.h"

#include "PongBall.h"
#include "PongPaddle.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH  600

#define PADDLE_WIDTH 150
#define PADDLE_HEIGHT 30

#include "PackageFile.h"
#include "TestRunner.h"

#include "ResourceManager.h"

int main()
{
    while (true)
    {
		PackageFile* pack = new PackageFile();
		pack->AddFile("assets\\texture.png");
		pack->AddFile("assets\\texture.png");
		pack->Save("package.pack");

		delete(pack);

        ResourceManager* resmon = new ResourceManager();
        resmon->Init(ResourceManagerInitParams::GetDefaultParams());

        // [](const int n) { return n == 8;}
		//auto overworldModules = resmon->Modules->Where([](const GameModule* p) {
		//	return strcmp(p->ModuleName.c_str(), "overworld") == 0;
		//});

		auto res = resmon->Resources->Get(0);

		int siz = 0;
		auto dat = res->GetData(siz);

		auto dat2 = res->GetData(siz);

        delete(resmon);
		
		delete(dat);

		//delete(overworldModules);

        int i = 0;
    }

	return 0;

    while (true)
    {
        XmlReader rdr;

        rdr.LoadFile("assets\\catalog.xml");

        auto ret = rdr.GetNodes("produce");;

        ret->Release();

        delete(ret);
    }


    return 0;

    PackageFile* p = new PackageFile();
    p->AddFile("C:\\temp\\notnull.txt");
    p->AddFile("C:\\temp\\new_test_file.txt");
    p->AddFile("C:\\temp\\BigFile.txt");
    p->Save("C:\\temp\\out.bin");


    PackageFile* p2 = new PackageFile("C:\\temp\\out.bin");
    int fileSize = 0;

    const char* fileContents1 = p2->GetFile("C:\\temp\\notnull.txt", fileSize);
    const char* fileContents2 = p2->GetFile("C:\\temp\\new_test_file.txt", fileSize);
    const char* fileContents3 = p2->GetFile("C:\\temp\\BigFile.txt", fileSize);

    return 0;

    // --- END TEST CODE ---

    // Below is game code
    BaseGraphicEngine* engine = new GraphicEngine();

    GraphicEngineInitParams* params = new GraphicEngineInitParams();
    params->EnableVerticalSync = true;
    params->WindowSize = new FSize(WINDOW_HEIGHT, WINDOW_WIDTH);
    params->WindowTitle = "PONG";

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
    PongPaddle* paddleTwo = new PongPaddle(paddleSpriteTwo);

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