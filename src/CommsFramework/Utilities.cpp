#include "Utilities.h"

#ifdef WIN32

#include <Windows.h>

#endif

void DumpData(const char* data, int size, std::string outputName)
{
    std::ofstream outStream = std::ofstream(outputName, std::ofstream::out | std::ofstream::binary);

    outStream.write(data, size);

    outStream.close();
}

int GetTicks()
{
#ifdef WIN32

    DWORD res = GetTickCount();

    return res;

#else
    return 0;
#endif
}

float SafeCharToFloat(char * data, float defaultValue)
{
    if (data == NULL)
    {
        return defaultValue;
    }
    else
    {
        float ret = atof(data); // Do additional checks ?

        return ret;
    }
}
