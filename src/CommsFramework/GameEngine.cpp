#include "GameEngine.h"

#include "SFMLGraphicEngine.h"

#include "GraphicEngineInitParams.h"
#include "ResourceManager.h"

#include "SFMLKeyboard.h"
#include "SFMLMouse.h"

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

#include "Resource.h"

#include "MouseClickInfo.h"

BaseKeyboard* GameEngine::Keyboard = 0;
BaseMouse* GameEngine::Mouse = 0;

GameEngine* GameEngine::_globalInstance;

GameEngine::GameEngine()
{
    GameEngine::_globalInstance = this;

    Graphics = new SFMLGraphicEngine();
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

    this->GameAreaSize = params->GraphicsParams->WindowSize;

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
    GameEngine::Mouse->UpdateMouseState();
    GameEngine::Keyboard->UpdateKeyboardState();

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

BaseSprite* GameEngine::CreateSprite(std::string spriteName)
{
    BaseSprite* sprt = this->Graphics->CreateSprite(spriteName);
    
    GameSprites->Add(sprt);
    this->Graphics->AddObject(sprt);

    return sprt;
}

BaseSprite* GameEngine::CreateSprite(std::string spriteName, std::string spriteTexturePath)
{
    BaseSprite* sprt = this->Graphics->CreateSprite(spriteName);

    BaseTexture* tex = this->Graphics->CreateTexture(spriteTexturePath);

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

BaseFont* GameEngine::GetGameDefaultFont()
{
    if (engineDefaultFont == NULL)
    {
        engineDefaultFont = this->Graphics->CreateFont();
        engineDefaultFont->Load("assets//arial.ttf");
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

    this->Graphics->GetDrawableList()->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

BaseText* GameEngine::CreateText(std::string text, int textSize)
{
    BaseText* ret = this->Graphics->CreateText();
    ret->SetText(text);
    ret->SetCharacterSize(textSize);
    ret->SetColor(0x000000FF);

    this->Graphics->GetDrawableList()->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

BaseText* GameEngine::CreateText(std::string text, int textSize, uint32_t textColor)
{
    BaseText* ret = this->Graphics->CreateText();
    ret->SetText(text);
    ret->SetCharacterSize(textSize);
    ret->SetColor(textColor);

    this->Graphics->GetDrawableList()->Add(ret);
    this->GameTexts->Add(ret);

    return ret;
}

BaseText* GameEngine::CreateText(std::string text, int textSize, uint32_t textColor, BaseFont * typo)
{
    BaseText* ret = this->Graphics->CreateText();
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

                if (strcmp(sprt->Ident.c_str(), "YesNoDialogYesButton") == 0)
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

GameEngineInitParams* GameEngineInitParams::CreateDefaultParams()
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