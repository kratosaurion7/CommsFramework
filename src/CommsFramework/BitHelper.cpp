#include "BitHelper.h"

int BytesToInt(char* characters)
{
    // Interpret the char array as an array of ints (used 4 bytes to make 1 int element) then take the first one
    // Credit : http://stackoverflow.com/a/30992344/377182
    int number = ((int*)characters)[0];

    return number;
}