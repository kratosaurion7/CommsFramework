#include "Spritesheet.h"

#include "BaseGraphicEngine.h"
#include "BaseSprite.h"
#include "BaseTexture.h"
#include "XmlReader.h"
#include "FRectangle.h"

Spritesheet::Spritesheet(std::string spritesheetPath, std::string configFilePath, BaseGraphicEngine* engine)
{
    spritesheetTexture = engine->CreateTexture(spritesheetPath);

    Graphics = engine;

    this->SpritesheetFilePath = spritesheetPath;
    this->ConfigFilePath = configFilePath;
}

Spritesheet::~Spritesheet()
{
}

PointerList<BaseSprite*>* Spritesheet::ExtractSprites()
{
    PointerList<BaseSprite*>* spriteList = new PointerList<BaseSprite*>();

    XmlReader configReader = XmlReader();
    configReader.LoadFile(this->ConfigFilePath);
    PointerList<XmlNode*>* nodes = configReader.GetNodes("sprite");

    auto it = nodes->GetContainer()->begin();
    while (it != nodes->GetContainer()->end())
    {
        XmlNode* node = (*it);

        std::string spriteName = node->GetAttribute("n").AttributeValue;
        int spriteSubTextureX = std::atoi(node->GetAttribute("x").AttributeValue);
        int spriteSubTextureY = std::atoi(node->GetAttribute("y").AttributeValue);
        int spriteSubTextureW = std::atoi(node->GetAttribute("w").AttributeValue);
        int spriteSubTextureH = std::atoi(node->GetAttribute("h").AttributeValue);

        FRectangle subRec = FRectangle(spriteSubTextureX, spriteSubTextureY, spriteSubTextureW, spriteSubTextureH);

        BaseSprite* newSprite = Graphics->CreateSprite(spriteName);
        BaseTexture* newSpriteTexture = spritesheetTexture->GetSubTexture(subRec);
        newSprite->SetTexture(newSpriteTexture);

        spriteList->Add(newSprite);

        it++;
    }

    nodes->Release();
    delete(nodes);

    return spriteList;
}

PointerList<BaseTexture*>* Spritesheet::ExtractTextures()
{
    PointerList<BaseTexture*>* textures = new PointerList<BaseTexture*>();

    XmlReader configReader = XmlReader();
    configReader.LoadFile(this->ConfigFilePath);
    PointerList<XmlNode*>* nodes = configReader.GetNodes("sprite");

    auto it = nodes->GetContainer()->begin();
    while (it != nodes->GetContainer()->end())
    {
        XmlNode* node = (*it);

        std::string textureName = node->GetAttribute("n").AttributeValue;
        int spriteSubTextureX = std::atoi(node->GetAttribute("x").AttributeValue);
        int spriteSubTextureY = std::atoi(node->GetAttribute("y").AttributeValue);
        int spriteSubTextureW = std::atoi(node->GetAttribute("w").AttributeValue);
        int spriteSubTextureH = std::atoi(node->GetAttribute("h").AttributeValue);

        FRectangle subRec = FRectangle(spriteSubTextureX, spriteSubTextureY, spriteSubTextureW, spriteSubTextureH);

        BaseTexture* newSpriteTexture = spritesheetTexture->GetSubTexture(subRec);
        newSpriteTexture->TextureName = textureName;

        textures->Add(newSpriteTexture);

        it++;
    }

    nodes->Release();
    delete(nodes);

    return textures;
}
