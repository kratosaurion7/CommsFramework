#include "SDLText.h"

SDLText::SDLText()
{
    isVisible = false;
    position = FPosition();
    positionOffset = FPosition();
    size = FSize();
    scale = FloatVec();
    scale.Set(1, 1);
    clippingBounds = FRectangle();

    Engine = NULL;
    ClickInfo = NULL;
}

SDLText::~SDLText()
{
}

std::string SDLText::GetText()
{
    return "";
}

void SDLText::SetText(std::string text)
{
}

BaseFont* SDLText::GetFont()
{
    return NULL;
}

void SDLText::SetFont(BaseFont* font)
{
}

int SDLText::GetCharacterSize()
{
    return 0;
}

void SDLText::SetCharacterSize(int size)
{
}

TextStyle SDLText::GetStyle()
{
    return TEXT_STYLE_REGULAR;
}

void SDLText::SetStyle(TextStyle style)
{
}

uint32_t SDLText::GetColor()
{
    return 0xFFFFFFFF;
}

void SDLText::SetColor(uint32_t color)
{
}

SDL_Texture* SDLText::GetDrawableTexture()
{
    return NULL;
}

void SDLText::UpdateInnerImpl()
{
}
