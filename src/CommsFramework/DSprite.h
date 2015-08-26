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

    // Get the list of animations of the Sprite.
    virtual PointerList<SpriteAnimation*>* GetAnimations();
    // Set a list of animation that the sprite can Play.
    virtual void SetAnimations(PointerList<SpriteAnimation*>* newAnims);
    // Get the current texture on the sprite.
    virtual DTexture* GetCurrentTexture();
    // Get all textures used by the sprite.
    virtual PointerList<BaseTexture*>* GetTextures();

    // Called when a Sprite is set to draw. This will advance to the next
    // frame if the frame is Visible and it is set as playing.
    // If not enough time has ellapsed between frames, the Sprite
    // will not draw.
    virtual void Draw();

    // Play the default animation, optionally set it to loop.
    virtual void Play(bool loop = false);
    // Play the animation with the given name, optionally set it to loop
    virtual void Play(std::string animName, bool loop = false);
    // Stop the current animation
    virtual void Stop();
    // Stop the animation and set the current frame to 0, of the default anim.
    virtual void Reset();

    /**
     * Move to the next frame of the current animation, then 
     * apply the new current texture. This also sets the lastFrameTick */
    virtual void NextFrame();
    /** Set the current frame to the target index, optionally
     *  giving an anim name to change the current animation. */
    virtual void SetFrame(int index, std::string animName = "");
    // Check if the current frame is pointing to the last frame index
    virtual bool IsLastFrame(std::string animName = "");

    /**
     * Set the current sprite texture to the specified texture.
     * The new texture will be casted to DTexture to be send to the 
     * innerImpl
     */
    virtual void SetTexture(BaseTexture* texture);

    // SFML Inner object
    sf::Sprite* innerImpl;
    
    /**
     * Function called by the graphic engine to retrieve the inner
     * SFML object implementation */
    sf::Drawable* GetDrawableImplementation();

    // Current playing animation of the Sprite.
    SpriteAnimation* CurrentAnimation;

private:
    /**
     * Check if the sprite is ready for another frame switch
     * given the sprite FPS */
    bool IsFrameReady();

    // System tick count of the last frame update, in milisecond.
    int lastFrameTick;

    /**
     * Shorthand function to search in the spriteAnimationList */
    SpriteAnimation* FindAnim(std::string name);

    // Texture currently on sprite.
    DTexture* spriteTexture; 
    // List of animations containing textures for the sprite.
    PointerList<SpriteAnimation*>* spriteAnimationList;

    /**
     *  Update the SFML sprite values, position, etc. */
    void UpdateInnerImpl();

    /**
    *   Apply the texure of the current animation at the current frame
    *   to the sprite. */
    void ApplyCurrentTexture();
};

