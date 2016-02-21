#pragma once

class GenType
{
public:
    struct SUPPORTED_TYPES
    {
        enum TYPES
        {
            INT32,
            BOOL,
            STRING,
            DATA
        };
    };

    GenType();
    ~GenType();

    SUPPORTED_TYPES::TYPES ValueType;
    void* Value;

    int ValueLength;
};

