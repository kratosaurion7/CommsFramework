#pragma once

#include <SFML\Graphics.hpp>

#include "BaseSprite.h"

#include "BaseTexture.h"
#include "DTexture.h"

#include "SFMLDrawable.h"

#include "FPosition.h"
#include "FRectangle.h"
#include "FSize.h"

#include "SpriteAnimation.h"

/*
 *
 */
class DSprite : public BaseSprite, public SFMLDrawable
{
public:
    DSprite();
    ~DSprite();

    sf::Sprite* innerImpl;

    virtual PointerList<SpriteAnimation*>* GetAnimations();
    virtual void SetAnimations(PointerList<SpriteAnimation*>* newAnims);
    virtual DTexture* GetCurrentTexture();
    virtual PointerList<BaseTexture*>* GetTextures();

    // Called when a Sprite is set to draw. This will advance to the next
    // frame if the frame is Visible and it is set as playing.
    // If not enough time has ellapsed between frames, the Sprite
    // will not draw.
    virtual void Draw();

    virtual void Play(bool loop = false);
    virtual void Play(std::string animName, bool loop = false);
    virtual void Stop();
    virtual void Reset();

    virtual void NextFrame();
    virtual void SetFrame(int index, std::string animName = "");
    virtual bool IsLastFrame(std::string animName = "");


    virtual void SetTexture(BaseTexture* texture);

    virtual BaseSprite* Clone();

    /**
     * Function called by the graphic engine to retrieve the inner
     * SFML object implementation */
    sf::Drawable* GetDrawableImplementation();

    bool IsAnimatedSprite();

    //virtual bool IsVisible();
private:
    // System tick count of the last frame update, in milisecond.
    int lastFrameTick;
    // Texture currently on sprite.
    DTexture* spriteTexture;
    // List of animations containing textures for the sprite.
    

    /**
     * Check if the sprite is ready for another frame switch
     * given the sprite FPS */
    bool IsFrameReady();

    /**
     * Shorthand function to search in the spriteAnimationList */
    SpriteAnimation* FindAnim(std::string name);

    /**
     *  Update the SFML sprite values, position, etc. */
    void UpdateInnerImpl();

    /**
    *   Apply the texure of the current animation at the current frame
    *   to the sprite. */
    void ApplyCurrentTexture();
};

