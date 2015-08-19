#include "SpriteDescriptor.h"

#include <stdio.h>

SpriteDescriptor::SpriteDescriptor()
{
    Frames = new BaseList<std::string>();

    FrameLists = new PointerList<Framelist*>();

    FrameResources = new PointerList<Resource*>();

    Module = NULL;
    position = NULL;
    size = NULL;
}

SpriteDescriptor::~SpriteDescriptor()
{
    delete(position);
    delete(size);

    delete(Frames);
    //delete(FrameResources);

    FrameLists->Release();
    delete(FrameLists);
}

BaseList<std::string>* Framelist::GetFrames()
{
    BaseList<std::string>* frames = new BaseList<std::string>();

    int substringIndexStart = pattern.find("%s");

    for (int i = startIndex; i < endIndex; i += step)
    {
        std::string newString = pattern.substr(0, substringIndexStart);

        newString.append(std::to_string(i));

        frames->Add(newString);
    }

    return frames;
}
