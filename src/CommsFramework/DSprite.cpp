#include "DSprite.h"

#include <SFML\Graphics.hpp>

#include "BaseSprite.h"

#include "BaseTexture.h"
#include "DTexture.h"

#include "FPosition.h"
#include "FSize.h"
#include "FRectangle.h"

DSprite::DSprite()
{
	innerImpl = new sf::Sprite();
	spriteTexture = NULL;
	isVisible = true;
	position = new FPosition();
	size = new FSize();
}

DSprite::~DSprite()
{
	// Don't delete the sprite texture when deleting a sprite, the texture might be shared around.
	delete innerImpl;
	delete position;
	delete size;
}

DTexture* DSprite::GetCurrentTexture()
{
    return spriteTexture;
}

PointerList<BaseTexture*>* DSprite::GetTextures()
{
    PointerList<BaseTexture*>* returnTextures = new PointerList<BaseTexture*>();

    auto it = spriteTextures->GetContainer()->begin();
    while (it != spriteTextures->GetContainer()->end())
    {
        DTexture* texture = (*it);
        returnTextures->Add(texture);
    }

    return returnTextures;
}

void DSprite::SetFrame(int index)
{
    spriteTexture = spriteTextures->Get(CurrentFrameIndex % FramesCount); // Modulo for safety.
}

void DSprite::SetTextures(PointerList<BaseTexture*>* textures)
{
    delete(spriteTextures);
    spriteTextures = new PointerList<DTexture*>();

    auto it = textures->GetContainer()->begin();
    while (it != textures->GetContainer()->end())
    {
        BaseTexture* texture = (*it);

        spriteTextures->Add((DTexture*)texture);
    }

    FramesCount = spriteTextures->Count();
}


//DTexture* DSprite::GetTexture()
//{
//	return spriteTexture;
//}
//
void DSprite::SetTexture(BaseTexture * texture)
{
    delete(spriteTexture); // Ok to delete ?

	DTexture* dtxr = dynamic_cast<DTexture*>(texture);

	if (dtxr != NULL)
	{
		innerImpl->setTexture((*dtxr->innerImpl));
		spriteTexture = dtxr;
		size = texture->GetSize();
	}
}

sf::Drawable * DSprite::GetDrawableImplementation()
{
	return innerImpl;
}

void DSprite::UpdateInnerImpl()
{
	innerImpl->setPosition(position->X, position->Y);
}
