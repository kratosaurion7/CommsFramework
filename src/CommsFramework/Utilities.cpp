#include "Utilities.h"

void DumpData(const char* data, int size)
{
    std::ofstream outStream = std::ofstream("output.test", std::ofstream::out | std::ofstream::binary);

    outStream.write(data, size);

    outStream.close();
};
