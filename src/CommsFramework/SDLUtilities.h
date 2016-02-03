#pragma once

class FRectangle;
class SDLSprite;
class SDLText;
struct SDL_Rect;

#include <string>

SDL_Rect FRectToSDL_Rect(FRectangle rec);

void SaveSpriteAsBMP(SDLSprite* sprt, std::string fileName);
void SaveTextAsBMP(SDLText* text, std::string fileName);