#pragma once

class FSize
{
public:
    FSize();
    FSize(float height, float width);
    ~FSize();

    float Height;

    float Width;

    void Set(float h, float w);
};

