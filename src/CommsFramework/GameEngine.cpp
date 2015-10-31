#include "GameEngine.h"

#include "GraphicEngine.h"
#include "FSize.h"

#include "Resource.h"

#include "PointerList.h"

#include "BaseKeyboard.h"
#include "BaseMouse.h"

#include "SFMLKeyboard.h"
#include "SFMLMouse.h"

BaseKeyboard* GameEngine::Keyboard = 0;
BaseMouse* GameEngine::Mouse = 0;

GameEngine::GameEngine()
{
    Graphics = new GraphicEngine();
    Resources = new ResourceManager();

    GameSprites = new PointerList<BaseSprite*>();
    GameActors = new PointerList<BaseActor*>();
    GameTexts = new PointerList<BaseText*>();

    SFMLKeyboard* sfKeyboard = new SFMLKeyboard();
    sfKeyboard->graphicsRef = this->Graphics;

    SFMLMouse* sfMouse = new SFMLMouse();
    sfMouse->engineRef = this->Graphics;

    GameEngine::Keyboard = sfKeyboard;
    GameEngine::Mouse = sfMouse;

    Rng = new RandomGen();

    engineDefaultFont = NULL;
    
    GameRules = new PointerList<GameRule*>();
}

GameEngine::~GameEngine()
{
    delete(engineInitParams);

    delete(Graphics);

    delete(Resources);

    //GameSprites->Release();
    delete(GameSprites);

    GameActors->Release();
    delete(GameActors);

    //GameTexts->Release();
    delete(GameTexts);

    GameRules->Release();
    delete(GameRules);
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

void GameEngine::Init(GameEngineInitParams * params)
{
    engineInitParams = params;

    Graphics->Initialize(params->GraphicsParams);

    Resources->Init(params->ResourceParams);
}

BaseSprite* GameEngine::GetSprite(std::string name)
{
    BaseSprite* existingSprite = GameSprites->Single([name](BaseSprite* sprt) { return sprt->Ident == name; });

    if (existingSprite != NULL)
    {
        return existingSprite;
    }

    // Get sprite
    BaseSprite* spriteObject = Graphics->CreateSprite(name);
    SpriteDescriptor* desc = Resources->SpritesInfo->Single([name](SpriteDescriptor* descriptor) { return descriptor->SpriteName.compare(name) == 0; });
    
    spriteObject->ApplyDescriptor(desc);

    PointerList<SpriteAnimation*>* spriteAnimations = Resources->GetAnimationsForSprite(spriteObject);

    BuildAnimationTextures(spriteAnimations);

    // At this point, the sprite anims have created their textures.
    spriteObject->SetAnimations(spriteAnimations);

    if (spriteObject != NULL)
    {
        GameSprites->Add(spriteObject);
    }

    return spriteObject;
}

BaseList<BaseSprite*>* GameEngine::GetSpriteList(std::string name)
{
    return GameSprites->Where([name](BaseSprite* sprite) { return sprite->Ident == name; });
}

BaseSprite * GameEngine::CopySprite(std::string targetSpriteName, std::string newName)
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

    Resources->Load();
}

void GameEngine::Play()
{
    this->Pre_Update(); // Update at start of loop

    this->Graphics->ProcessEvents();

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

        act->Update();

        it++;
    }
}

void GameEngine::Draw()
{
    this->Graphics->Draw();

    auto it = GameSprites->GetContainer()->begin();
    while (it != GameSprites->GetContainer()->end())
    {
        BaseSprite* sprite = *it;
        sprite->Draw();

        it++;
    }
}

void GameEngine::Post_Update()
{
    GameEngine::Mouse->UpdateMouseState();
    GameEngine::Keyboard->UpdateKeyboardState();

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

BaseActor * GameEngine::CreateActor()
{
    BaseActor* newActor = new BaseActor();
    newActor->Engine = this;

    this->GameActors->Add(newActor);

    return newActor;
}

BaseActor * GameEngine::CreateActor(BaseSprite * actorSprite)
{
    BaseActor* newActor = new BaseActor();
    newActor->Engine = this;

    newActor->Sprites->Add(actorSprite);

    this->GameActors->Add(newActor);

    return newActor;
}

BaseActor * GameEngine::CreateActor(PointerList<DrawObject*>* spriteList)
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

BaseSprite * GameEngine::CreateSprite(std::string spriteName)
{
    BaseSprite* sprt = this->Graphics->CreateSprite(spriteName);
    
    GameSprites->Add(sprt);
    this->Graphics->AddObject(sprt);

    return sprt;
}

BaseSprite * GameEngine::CreateSprite(std::string spriteName, std::string spriteTexturePath)
{
    BaseSprite* sprt = this->Graphics->CreateSprite(spriteName);

    BaseTexture* tex = this->Graphics->CreateTexture();
    tex->Load(spriteTexturePath);

    if(tex != NULL)
        sprt->SetTexture(tex);

    GameSprites->Add(sprt);
    this->Graphics->AddObject(sprt);

    return sprt;
}

BaseFont * GameEngine::GetGameDefaultFont()
{
    if (engineDefaultFont == NULL)
    {
        engineDefaultFont = this->Graphics->CreateFont();
        engineDefaultFont->Load("assets/arial.ttf");
    }

    return engineDefaultFont;
}

BaseText* GameEngine::CreateText(std::string text)
{
    BaseText* ret = this->Graphics->CreateText();
    ret->SetText(text);
    ret->SetCharacterSize(36);
    ret->SetColor(0x000000FF);
    ret->SetFont(this->GetGameDefaultFont());

    this->Graphics->Sprites->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

BaseText* GameEngine::CreateText(std::string text, BaseFont* typo)
{
    BaseText* ret = this->Graphics->CreateText();
    ret->SetText(text);
    ret->SetCharacterSize(36);
    ret->SetColor(0x000000FF);
    ret->SetFont(typo);

    this->Graphics->Sprites->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

BaseText* GameEngine::CreateText(std::string text, BaseFont* typo, int textSize)
{
    BaseText* ret = this->Graphics->CreateText();
    ret->SetText(text);
    ret->SetCharacterSize(textSize);
    ret->SetColor(0x000000FF);
    ret->SetFont(typo);

    this->Graphics->Sprites->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

void GameEngine::FlagClickedSprites()
{
    if (this->Mouse->IsClicked())
    {
        FloatVec mousePos = this->Mouse->GetMousePosition();

        auto it = this->Graphics->Sprites->GetContainer()->begin();
        while (it != this->Graphics->Sprites->GetContainer()->end())
        {
            DrawObject* sprt = (*it);

            if (sprt->IsVisible())
            {
                FRectangle bounds = sprt->GetRectangle();
                bool containmentTest = bounds.IsPointInside(mousePos);

                if (containmentTest)
                {
                    sprt->isClicked = true;

                    bool eventHandled = true;

                    if (eventHandled)
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
    auto it = this->Graphics->Sprites->GetContainer()->begin();
    while (it != this->Graphics->Sprites->GetContainer()->end())
    {
        DrawObject* sprt = (*it);

        sprt->isClicked = false;

        it++;
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

PointerList<BaseTexture*>* GameEngine::CreateTexturesFromResources(PointerList<Resource*>* resources)
{
    PointerList<BaseTexture*>* textureList = new PointerList<BaseTexture*>();

    int counter = 0;

    auto it = resources->GetContainer()->begin();
    while (it != resources->GetContainer()->end())
    {
        Resource* res = (*it);

        BaseTexture* newTexture = Graphics->CreateTexture();

        int dataSize = 0;
        char* resourceData = res->GetData(dataSize);

        newTexture->LoadFromMemory(resourceData, dataSize);

        textureList->Add(newTexture);
        counter++;
        it++;
    }

    return textureList;
}

void GameEngine::BuildAnimationTextures(PointerList<SpriteAnimation*>* anims)
{
    auto it = anims->GetContainer()->begin();
    while (it != anims->GetContainer()->end())
    {
        SpriteAnimation* anim = *it;

        anim->AnimationFrames = CreateTexturesFromResources(anim->AnimationResources);

        it++;
    }
}

GameEngineInitParams * GameEngineInitParams::CreateDefaultParams()
{
    GameEngineInitParams* newParams = new GameEngineInitParams();

    ResourceManagerInitParams* newResourceParams = new ResourceManagerInitParams();
    newResourceParams->AssetRootFolder = "Assets\\";
    newResourceParams->ConfigFileLocation = "config.xml";
    newParams->ResourceParams = newResourceParams;

    GraphicEngineInitParams* newEngineParams = new GraphicEngineInitParams();
    newEngineParams->EnableVerticalSync = true;
    newEngineParams->WindowSize = new FSize(600, 600);
    newEngineParams->WindowTitle = "DEFAULT WINDOW TITLE";
    newParams->GraphicsParams = newEngineParams;

    return newParams;
}