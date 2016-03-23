#include "Spritesheet.h"

#include "BaseGraphicEngine.h"
#include "BaseSprite.h"
#include "BaseTexture.h"
#include "XmlReader.h"
#include "FRectangle.h"

Spritesheet::Spritesheet(std::string spritesheetPath, BaseGraphicEngine* engine)
{
    spritesheetTexture = engine->CreateTexture(spritesheetPath);

    Graphics = engine;
}


Spritesheet::~Spritesheet()
{
}

PointerList<BaseSprite*>* Spritesheet::ExtractSprites(std::string configFilePath)
{
    PointerList<BaseSprite*>* spriteList = new PointerList<BaseSprite*>();

    XmlReader configReader = XmlReader();
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


    return spriteList;
}
