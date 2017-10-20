#include "StringFunctions.h"


BaseList<std::string>* StringSplit(std::string str, const char* delimiter)
{
    BaseList<std::string>* parts = new BaseList<std::string>();

    const char* originalString = str.c_str();
    char* tokeningString = new char[strlen(originalString) + 1];

    memcpy(tokeningString, originalString, strlen(originalString) + 1);

    char* foundToken;

    foundToken = strtok(tokeningString, delimiter);
    
    while (foundToken != NULL)
    {
        parts->Add(foundToken);

        foundToken = strtok(NULL, delimiter); // Second calls to strtok sends a NULL to the first parameter.
    }

    return parts;
}

std::string StringSubtract(std::string a, std::string b)
{
    int startPosition = (int)a.find(b, 0) + (int)b.length();

    std::string result = a.substr(startPosition, a.length() - b.length());

    return result;
}
