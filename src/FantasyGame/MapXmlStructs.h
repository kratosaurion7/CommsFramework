#pragma once

struct TileDescriptionEntry;

#include <string>
#include <Collections/PointerList.h>

struct TileDescriptionList
{
    PointerList<TileDescriptionEntry*>* Entries;
};

struct TileDescriptionEntry
{
    int id;
    std::string TextureName;
};