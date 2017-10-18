#include "Utilities.h"

#ifdef WIN32

#include <Windows.h>

#elif linux

#include <sys/time.h>

#elif __EMSCRIPTEN__

#include <emscripten.h>

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

#elif linux
    
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0)
            return 0;

    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#elif __EMSCRIPTEN__
    return emscripten_get_now();
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
