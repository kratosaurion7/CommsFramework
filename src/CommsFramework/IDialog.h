#pragma once

class IDialog
{
public:
    virtual void Open() = 0;

    virtual void Close() = 0;

    virtual bool IsOpen() = 0;
};