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

    textContent = "";

    Engine = NULL;
    ClickInfo = NULL;
}

SDLText::~SDLText()
{
}

std::string SDLText::GetText()
{
    return textContent;
}

void SDLText::SetText(std::string text)
{
    if (textContent.compare(text) != 0)
    {
        textContent = text;
        
        this->UpdateInnerImpl();
    }
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
