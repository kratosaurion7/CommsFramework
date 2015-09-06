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

    SFMLKeyboard* sfKeyboard = new SFMLKeyboard();
    sfKeyboard->graphicsRef = this->Graphics;

    SFMLMouse* sfMouse = new SFMLMouse();
    sfMouse->engineRef = this->Graphics;

    GameEngine::Keyboard = sfKeyboard;
    GameEngine::Mouse = sfMouse;
    
}

GameEngine::~GameEngine()
{
    delete(engineInitParams);

    delete(Graphics);

    delete(Resources);

    GameSprites->Release();
    delete(GameSprites);
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
}

void GameEngine::Pre_Update()
{
}

void GameEngine::Update()
{
}

void GameEngine::Post_Update()
{
    GameEngine::Mouse->UpdateMouseState();
}

void GameEngine::CreateSpritesFromConfig()
{

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