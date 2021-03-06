#pragma once

class BaseSprite;
class BaseText;
class BaseTexture;
class BaseFont;
class Spritesheet;
class ViewportRect;
struct PrimitiveDrawInfo;

class GraphicEngineInitParams;

#include <string>

#include "Graphic/Base Classes/BaseSprite.h"
#include "Graphic/Base Classes/BaseText.h"
#include "Graphic/Base Classes/BaseFont.h"
#include "Graphic/Base Classes/BaseTexture.h"
#include "Graphic/Base Classes/BaseKeyboard.h"
#include "Collections/PointerList.h"
#include "Graphic/GraphicEngineInitParams.h"
#include "Graphic/TextureManager.h"
#include "Geometry/FPosition.h"
#include "Geometry/FRectangle.h"

class BaseGraphicEngine
{
public:
    BaseGraphicEngine();
    virtual ~BaseGraphicEngine() = 0;

    TextureManager* TextureRepo;

    ViewportRect* Viewport;

    bool zIndexNeedsReordering = false;

    int WantedFrameRate;

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


    virtual BaseSprite* CreateSprite();
    virtual BaseFont* CreateFont();
    virtual BaseText* CreateText();

    virtual BaseTexture* CreateTexture();
    virtual BaseTexture* CreateTexture(std::string textureName);
    virtual BaseTexture* CreateTexture(std::string textureName, std::string texturePath);

    // Primitive drawing methods
    virtual void SetPrimitiveDrawParameters(uint32_t color, int zIndex);

    virtual void DrawLine(FPosition* pointA, FPosition* pointB);
    virtual void DrawLine(FPosition* pointsArray, int arrayLength);
    virtual void DrawLine(float xA, float yA, float xB, float yB);

    virtual void DrawRect(FRectangle* rec);
    virtual void DrawRect(FPosition* startCorner, FPosition* opposingCorner);
    virtual void DrawRect(float x, float y, float height, float width);

    virtual void ReloadSpriteTextures() = 0;

    virtual bool IsTimeForFrame();
    virtual int GetFramerate();
    virtual void SetFramerate(int framerate);
    virtual void SetAutoManagedFramerate(bool isSet);

    virtual void SetBackgroundColor(uint32_t color) = 0;
    virtual void SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) = 0;

    virtual void SetBackgroundTexture(BaseTexture* texture) = 0;

    virtual void Scale(float scaleFactor) = 0;

    // Flow Control methods
    virtual void Start() = 0;

    virtual void Draw() = 0;

    virtual void ProcessEvents() = 0;

    virtual void Stop() = 0;

    virtual bool IsRunning() = 0;

    // Z-Index management methods
    virtual void ReorderSpritesByZIndex() = 0;

    virtual void FlagForZIndexSorting() = 0;

    virtual void ReorderSprite(DrawObject* first, DrawObject* second) = 0;

//protected:
    virtual BaseSprite* CreateSpriteInstance() = 0;
    virtual BaseTexture* CreateTextureInstance() = 0;
    virtual BaseFont* CreateFontInstance() = 0;
    virtual BaseText* CreateTextInstance() = 0;

    int primitiveDrawZIndex = 1;
    uint32_t primitiveDrawColor = 0xFF000000;

    PointerList<PrimitiveDrawInfo*> PrimitiveDrawables;
};

inline BaseGraphicEngine::~BaseGraphicEngine() { };