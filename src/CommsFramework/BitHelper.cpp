#include "BitHelper.h"

int BytesToInt(char* characters)
{
    // Interpret the char array as an array of ints (used 4 bytes to make 1 int element) then take the first one
    // Credit : http://stackoverflow.com/a/30992344/377182
    int number = ((int*)characters)[0];

    return number;
}

unsigned char* IntToBytes(int integer)
{
    unsigned char bytes[4];
    unsigned long n = integer;

    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;

    return bytes;
}
