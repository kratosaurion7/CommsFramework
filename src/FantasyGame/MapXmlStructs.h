#pragma once

struct TileDescriptionEntry;

#include <string>
#include <PointerList.h>

struct TileDescriptionList
{
    PointerList<TileDescriptionEntry*>* Entries;
};

struct TileDescriptionEntry
{
    int id;
    std::string TextureName;
};