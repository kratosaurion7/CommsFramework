#include "StringFunctions.h"


BaseList<std::string>* StringSplit(std::string str, char* delimiter)
{
    BaseList<std::string>* parts = new BaseList<std::string>();

    const char* originalString = str.c_str();
    char* tokeningString = new char[strlen(originalString)];

    memcpy(tokeningString, originalString, strlen(originalString));

    char* foundToken;

    foundToken = strtok(tokeningString, delimiter);
    
    while (foundToken != NULL)
    {
        foundToken = strtok(NULL, delimiter); // Second calls to strtok sends a NULL to the first parameter.

        parts->Add(foundToken);
    }

    return parts;
}
