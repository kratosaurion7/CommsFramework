#pragma once

class BaseSprite;
class BaseText;
class BaseTexture;
class BaseFont;
class Spritesheet;

class GraphicEngineInitParams;
class TextureRepository;

#include "BaseSprite.h"
#include "BaseText.h"
#include "BaseFont.h"
#include "BaseTexture.h"
#include "BaseKeyboard.h"

#include "GraphicEngineInitParams.h"

#include "TextureRepository.h"

#include <string>

class BaseGraphicEngine
{
public:
    virtual ~BaseGraphicEngine() = 0;

    TextureRepository* TextureRepo;

    bool zIndexNeedsReordering = false;

    float DiagonalDPI;
    float HorizontalDPI;
    float VerticalDPI;

    float RenderingScaleX;
    float RenderingScaleY;

    int PreviousFrameTick;
    int CurrentFrameTick;

    virtual void Initialize(GraphicEngineInitParams* params) = 0;

    virtual void AddObject(BaseSprite* obj) = 0;
    virtual void AddObject(BaseText* obj) = 0;
    virtual void RemoveObject(DrawObject* obj) = 0;

    virtual void AddSpritesheet(Spritesheet* spritesheet) = 0;

    virtual PointerList<DrawObject*>* GetDrawableList() = 0;
    virtual DrawObject* GetDrawableObject(std::string identifier) = 0;

    virtual BaseSprite* CreateSpriteInstance() = 0;
    virtual BaseTexture* CreateTextureInstance() = 0;
    virtual BaseFont* CreateFontInstance() = 0;
    virtual BaseText* CreateTextInstance() = 0;

    virtual void ReloadSpriteTextures() = 0;

    virtual bool IsTimeForFrame() = 0;
    virtual int GetFramerate() = 0;
    virtual void SetFramerate(int framerate) = 0;
    virtual void SetAutoManagedFramerate(bool isSet) = 0;

    virtual void SetBackgroundColor(uint32_t color) = 0;
    virtual void SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) = 0;

    virtual void SetBackgroundTexture(BaseTexture* texture) = 0;

    virtual void Scale(float scaleFactor) = 0;

    virtual void Start() = 0;

    virtual void Draw() = 0;

    virtual void ProcessEvents() = 0;

    virtual void Stop() = 0;

    virtual bool IsRunning() = 0;

    virtual void ReorderSpritesByZIndex() = 0;

    virtual void FlagForZIndexSorting() = 0;

    virtual void ReorderSprite(DrawObject* first, DrawObject* second) = 0;

};

inline BaseGraphicEngine::~BaseGraphicEngine() { };