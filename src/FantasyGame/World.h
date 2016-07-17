#pragma once

class AreaGrid;
class XmlNode;

#include <string>
#include <PointerList.h>

class World
{
public:
    World();
    ~World();

    PointerList<AreaGrid*>* Areas;

    std::string WorldName;

    void SetupAreas(XmlNode* areasNode);
};

