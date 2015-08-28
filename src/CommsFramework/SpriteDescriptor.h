#pragma once

#include "FPosition.h"
#include "FSize.h"

#include <string>

#include "GameModule.h"

#include "BaseList.h"

#include "SpriteAnimation.h"

class Framelist {
public:
    int startIndex;
    int endIndex;
    int step;
    std::string pattern;

    BaseList<std::string>* GetFrames();
};

class GameModule;
class SpriteAnimation;

class SpriteDescriptor {
public:
    SpriteDescriptor();

    ~SpriteDescriptor();

    std::string SpriteName;

    GameModule* Module;

    FPosition Position;
    FSize Size;

    PointerList<SpriteAnimation*>* Animations;

    BaseList<std::string>* Frames;

    PointerList<Framelist*>* FrameLists;

    PointerList<Resource*>* FrameResources;
};

