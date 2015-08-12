#pragma once

enum FILE_OPEN_MODE
{
    FILE_READ,
    FILE_WRITE,
    FILE_READ_WRITE
};

enum FILE_SHARE_MODE
{
    NONE,
    SHARE_READ,
    SHARE_WRITE
};


class WindowsFile
{
public:
    WindowsFile();
    ~WindowsFile();

    
};

