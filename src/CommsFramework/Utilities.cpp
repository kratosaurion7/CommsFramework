#include "Utilities.h"

void DumpData(const char* data, int size, std::string outputName)
{
    std::ofstream outStream = std::ofstream(outputName, std::ofstream::out | std::ofstream::binary);

    outStream.write(data, size);

    outStream.close();
};
