#pragma once

#include <string>

enum ResourceType
{
    RES_IMG,
    RES_FONT,
    RES_AUDIO
};

class Resource
{
public:
    Resource();
    ~Resource();

    std::string Name;

    ResourceType Type;

    std::string Format;
};

