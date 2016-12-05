#include "GameEngine.h"

#include "SDLKeyboard.h"
#include "SDLMouse.h"
#include "SDLGraphicEngine.h"
#include <SDL_events.h>

#include "GraphicEngineInitParams.h"


#include "SFMLKeyboard.h"
#include "SFMLMouse.h"

#include "ConfigurationManager.h"

#include "BaseKeyboard.h"
#include "BaseMouse.h"
#include "BaseGraphicEngine.h"
#include "BaseActor.h"
#include "BaseSprite.h"

#include "MouseClickInfo.h"
#include "GameRule.h"
#include "RandomGen.h"
#include "EngineDialogMessage.h"
#include "BaseQueue.h"


#include "FSize.h"

#include "MouseClickInfo.h"

BaseKeyboard* GameEngine::Keyboard = 0;
BaseMouse* GameEngine::Mouse = 0;

GameEngine* GameEngine::_globalInstance;

GameEngine::GameEngine()
{
    GameEngine::_globalInstance = this;

    Graphics = new SDLGraphicEngine();

    GameSprites = new PointerList<BaseSprite*>();
    GameActors = new PointerList<BaseActor*>();
    GameTexts = new PointerList<BaseText*>();

    SDLKeyboard* sfKeyboard = new SDLKeyboard();
    //sfKeyboard->graphicsRef = this->Graphics;

    SDLMouse* sfMouse = new SDLMouse();
    //sfMouse->engineRef = this->Graphics;

    GameEngine::Keyboard = sfKeyboard;
    GameEngine::Mouse = sfMouse;

    this->ConfigManager = new ConfigurationManager();

    this->FrameClickInfo = NULL;

    Rng = new RandomGen();

    engineDefaultFont = NULL;
    
    GameRules = new PointerList<GameRule*>();
}

GameEngine::~GameEngine()
{
    // Deleted owned ressources
    GameActors->Release();
    GameRules->Release();

    // Delete pointers
    delete(engineInitParams);
    delete(Graphics);
    delete(Resources);
    delete(FrameClickInfo);
    delete(GameSprites);
    delete(GameActors);
    delete(GameTexts);
    delete(GameRules);
}

GameEngine* GameEngine::GetInstance()
{
    return GameEngine::_globalInstance;
}

void GameEngine::Init()
{
    GameEngineInitParams* defaultParams = GameEngineInitParams::CreateDefaultParams();
    
    this->Init(defaultParams);
}

void GameEngine::Init(int windowWidth, int windowHeight)
{
    GameEngineInitParams* defaultParams = GameEngineInitParams::CreateDefaultParams();

    defaultParams->GraphicsParams->WindowSize->Set(windowHeight, windowWidth);

    this->Init(defaultParams);
}

void GameEngine::Init(GameEngineInitParams* params)
{
    engineInitParams = params;

    this->ConfigManager->LoadConfig();

    this->GameAreaSize = params->GraphicsParams->WindowSize;

    Graphics->Initialize(params->GraphicsParams);
}

BaseSprite* GameEngine::GetSprite(std::string name)
{
    BaseSprite* existingSprite = GameSprites->Single([name](BaseSprite* sprt) { return sprt->Ident == name; });

    return existingSprite;
}

BaseList<BaseSprite*>* GameEngine::GetSpriteList(std::string name)
{
    return GameSprites->Where([name](BaseSprite* sprite) { return sprite->Ident == name; });
}

BaseSprite* GameEngine::CopySprite(std::string targetSpriteName, std::string newName)
{
    BaseSprite* orig = GetSprite(targetSpriteName);

    BaseSprite* newSprite = orig->Clone();

    if (newSprite != NULL)
    {
        newSprite->Ident = newName;

        GameSprites->Add(newSprite);
    }

    return newSprite;
}

void GameEngine::Load()
{
    CreateSpritesFromConfig();
}

void GameEngine::Play()
{
    this->DoEventLoop();

    this->Pre_Update(); // Update at start of loop

    this->Update(); // Update just before draw

    this->Draw();

    this->Post_Update(); // Update just before end of loop
}

void GameEngine::Pre_Update()
{
    if (this->Graphics->zIndexNeedsReordering)
    {
        this->Graphics->ReorderSpritesByZIndex();
    }

    this->FlagClickedSprites();
}

void GameEngine::Update()
{
    auto it = this->GameActors->GetContainer()->begin();
    while (it != this->GameActors->GetContainer()->end())
    {
        BaseActor* act = (*it);

        act->UpdateActor();

        it++;
    }
}

void GameEngine::Draw()
{
    auto it = GameSprites->GetContainer()->begin();
    while (it != GameSprites->GetContainer()->end())
    {
        BaseSprite* sprite = *it;

        sprite->Draw();

        it++;
    }

    this->Graphics->Draw();
}

void GameEngine::Post_Update()
{
    // ===== Update Game rules =====
    auto it = GameRules->GetContainer()->begin();
    while (it != GameRules->GetContainer()->end())
    {
        GameRule* rule = (*it);
        rule->Update(this);

        it++;
    }

    RemoveSpriteClickedFlag();

}

BaseActor* GameEngine::CreateActor()
{
    BaseActor* newActor = new BaseActor();
    newActor->Engine = this;

    this->GameActors->Add(newActor);

    return newActor;
}

BaseActor* GameEngine::CreateActor(BaseSprite * actorSprite)
{
    BaseActor* newActor = new BaseActor();
    newActor->Engine = this;

    newActor->Sprites->Add(actorSprite);

    this->GameActors->Add(newActor);

    return newActor;
}

BaseActor* GameEngine::CreateActor(PointerList<DrawObject*>* spriteList)
{
    BaseActor* newActor = new BaseActor();
    delete(newActor->Sprites); // TODO : Maybe find a better way to do that.
    newActor->Sprites = spriteList;

    this->GameActors->Add(newActor);

    return newActor;
}

void GameEngine::AttachActor(BaseActor* actor)
{
    this->GameActors->Add(actor);
    actor->Engine = this;
}

void GameEngine::DetachActor(BaseActor* actor)
{
    this->GameActors->RemoveObject(actor);
}

BaseSprite * GameEngine::CreateSprite()
{
    return this->CreateSprite("");
}

BaseSprite* GameEngine::CreateSprite(std::string spriteName)
{
    BaseSprite* sprt = this->Graphics->CreateSpriteInstance();
    sprt->Ident = spriteName;
    
    GameSprites->Add(sprt);
    this->Graphics->AddObject(sprt);

    return sprt;
}

BaseSprite* GameEngine::CreateSprite(std::string spriteName, std::string spriteTexturePath)
{
    BaseSprite* sprt = this->Graphics->CreateSpriteInstance();
    sprt->Ident = spriteName;

    //BaseTexture* tex = this->Graphics->TextureRepo->Create(spriteTexturePath);
    BaseTexture* tex = this->Graphics->TextureRepo->LoadFromDisk(spriteTexturePath);

    

    if(tex != NULL)
        sprt->SetTexture(tex);
    

    GameSprites->Add(sprt);
    this->Graphics->AddObject(sprt);

    return sprt;
}

void GameEngine::RemoveSprite(BaseSprite* sprite)
{
    this->GameSprites->RemoveObject(sprite);
    this->Graphics->RemoveObject(sprite);
}

BaseTexture* GameEngine::CreateTexture()
{
	BaseTexture* texture = this->Graphics->CreateTextureInstance();

	return texture;
}

BaseFont* GameEngine::CreateFont()
{
	BaseFont* newFont = this->Graphics->CreateFontInstance();

	return newFont;
}

BaseFont* GameEngine::GetGameDefaultFont()
{
    if (engineDefaultFont == NULL)
    {
        engineDefaultFont = this->Graphics->CreateFontInstance();
        engineDefaultFont->LoadFontFile("assets//arial.ttf");
        

        //BaseTexture* spriteFontTexture = this->Graphics->CreateTexture("assets//DefaultSpriteFont.png");
        //
        //int glyphsLen = 0;
        //SpriteFontGlyph** glyphMap = BaseFont::BuildDefaultFontGlyphDescriptor(glyphsLen);
        //engineDefaultFont->LoadSpriteFont(spriteFontTexture, glyphMap, glyphsLen);
    }

    return engineDefaultFont;
}

BaseText* GameEngine::CreateText(std::string text)
{
    BaseText* ret = this->Graphics->CreateTextInstance();
    ret->SetText(text);
    ret->SetCharacterSize(36);
    ret->SetColor(0x000000FF);
    ret->SetFont(this->GetGameDefaultFont());

    this->Graphics->GetDrawableList()->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

BaseText* GameEngine::CreateText(std::string text, int textSize)
{
    BaseText* ret = this->Graphics->CreateTextInstance();
    ret->SetText(text);
    ret->SetCharacterSize(textSize);
    ret->SetColor(0x000000FF);
    ret->SetFont(this->GetGameDefaultFont());

    this->Graphics->GetDrawableList()->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

BaseText* GameEngine::CreateText(std::string text, int textSize, uint32_t textColor)
{
    BaseText* ret = this->Graphics->CreateTextInstance();
    ret->SetText(text);
    ret->SetCharacterSize(textSize);
    ret->SetColor(textColor);
    ret->SetFont(this->GetGameDefaultFont());

    this->Graphics->GetDrawableList()->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

BaseText* GameEngine::CreateText(std::string text, int textSize, uint32_t textColor, BaseFont* typo)
{
    BaseText* ret = this->Graphics->CreateTextInstance();
    ret->SetText(text);
    ret->SetCharacterSize(textSize);
    ret->SetColor(textColor);
    ret->SetFont(typo);

    this->Graphics->GetDrawableList()->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

void GameEngine::RemoveText(BaseText* text)
{
    this->GameTexts->RemoveObject(text);
    this->Graphics->RemoveObject(text);
}

void GameEngine::ShowEngineDialog(std::string engineMessageForDialog)
{

}

void GameEngine::FlagClickedSprites()
{
    if (this->Mouse->IsClicked())
    {
        FloatVec mousePos = this->Mouse->GetMousePosition();

        MouseClickInfo* clickInfo = new MouseClickInfo();
        clickInfo->LeftButtonClicked = this->Mouse->LeftButtonClicked();
        clickInfo->RightButtonClicked = this->Mouse->RightButtonClicked();
        clickInfo->MiddleButtonClicked = this->Mouse->MiddleButtonClicked();
        clickInfo->clickPos = mousePos;
        
        this->FrameClickInfo = clickInfo;

        auto it = this->Graphics->GetDrawableList()->GetContainer()->rbegin();
        while (it != this->Graphics->GetDrawableList()->GetContainer()->rend())
        {
            DrawObject* sprt = (*it);

            if (sprt->IsVisible())
            {
                FRectangle bounds = sprt->GetRectangle();
                bool containmentTest = bounds.IsPointInside(mousePos);

                if (strcmp(sprt->Ident.c_str(), "BetButtonAccept") == 0)
                {
                    int i = 0;
                }

                if (containmentTest)
                {
                    sprt->ClickInfo = clickInfo;

                    if (!sprt->PropagateClicks)
                    {
                        break;
                    }
                }
            }

            it++;
        }
    }
}

void GameEngine::RemoveSpriteClickedFlag()
{
    auto it = this->Graphics->GetDrawableList()->GetContainer()->begin();
    while (it != this->Graphics->GetDrawableList()->GetContainer()->end())
    {
        DrawObject* sprt = (*it);

        sprt->ClickInfo = NULL;

        it++;
    }

    if (this->FrameClickInfo != NULL)
    {
        delete(FrameClickInfo);
        FrameClickInfo = NULL;
    }
        
}

void GameEngine::DoEventLoop()
{
    GameEngine::Mouse->UpdatePastMouseState();
    GameEngine::Keyboard->UpdateKeyboardState();

    SDL_Event myEvent;
    while (SDL_PollEvent(&myEvent)) {
        switch (myEvent.type)
        {
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                ((SDLMouse*)Mouse)->HandleEvent(&myEvent);
                break;
            }
            case SDL_QUIT:
            {
                exit(0);

                break;
            }
            case SDL_WINDOWEVENT:
            {
                break;
            }
            default:
                break;
        }
    }
}

void GameEngine::CreateSpritesFromConfig()
{

}

void GameEngine::UpdateGraphicEngineSpritesFromActors()
{
    auto it = GameActors->GetContainer()->begin();
    while (it != GameActors->GetContainer()->end())
    {
        BaseActor* act = (*it);
        
        auto actorIt = act->Sprites->GetContainer()->begin();
        while (actorIt != act->Sprites->GetContainer()->end())
        {
            DrawObject* sprt = (*actorIt);

            //if (!Graphics->Sprites->Contains(sprt))
            //{

            //}

            actorIt++;
        }

        it++;
    }
}

GameEngineInitParams* GameEngineInitParams::CreateDefaultParams()
{
    GameEngineInitParams* newParams = new GameEngineInitParams();

    GraphicEngineInitParams* newEngineParams = new GraphicEngineInitParams();
    newEngineParams->EnableVerticalSync = true;
    newEngineParams->WindowSize = new FSize(600, 600);
    newEngineParams->WindowTitle = "DEFAULT WINDOW TITLE";
    newParams->GraphicsParams = newEngineParams;

    return newParams;
}