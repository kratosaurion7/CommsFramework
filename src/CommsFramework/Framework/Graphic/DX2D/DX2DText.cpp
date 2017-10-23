#ifdef WIN32
#include "DX2DText.h"

std::string DX2DText::GetText()
{
    return "";
}

void DX2DText::SetText(std::string text)
{
    
}

BaseFont* DX2DText::GetFont()
{
    return NULL;
}

void DX2DText::SetFont(BaseFont* font)
{
    
}

int DX2DText::GetCharacterSize()
{
    return 0;
}

void DX2DText::SetCharacterSize(int size)
{
    
}

TextStyle DX2DText::GetStyle()
{
    return TextStyle::TEXT_STYLE_REGULAR;
}

void DX2DText::SetStyle(TextStyle style)
{
    
}

uint32_t DX2DText::GetColor()
{
    return 0;
}

void DX2DText::SetColor(uint32_t color)
{
    
}

BaseTexture* DX2DText::GetTextImage()
{
    return NULL;
}
IWICBitmapSource * DX2DText::GetDrawableTexture()
{
    return this->textTexture;
}
void DX2DText::UpdateInnerImpl()
{
}
void DX2DText::SetGraphicalFilter(int graphic_filter)
{

}
#endif