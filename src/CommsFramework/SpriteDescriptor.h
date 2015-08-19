#pragma once

#include "FPosition.h"
#include "FSize.h"

#include <string>

#include "GameModule.h"

#include "BaseList.h"

class Framelist {
public:
    int startIndex;
    int endIndex;
    int step;
    std::string pattern;

    BaseList<std::string>* GetFrames();
};

class GameModule;

class SpriteDescriptor {
public:
    SpriteDescriptor();

    ~SpriteDescriptor();

    std::string SpriteName;

    GameModule* Module;

    FPosition* position;
    FSize* size;

    BaseList<std::string>* Frames;

    PointerList<Framelist*>* FrameLists;

    PointerList<Resource*>* FrameResources;
};

