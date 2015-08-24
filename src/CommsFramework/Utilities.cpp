#include "Utilities.h"

#ifdef _WINDOWS

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
#ifdef _WINDOWS

    DWORD res = GetTickCount();

    return res;

#elif
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
