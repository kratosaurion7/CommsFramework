#include "BitHelper.h"

int BytesToInt(char* characters)
{
	int number = (characters[3] << 24) + (characters[2] << 16) + (characters[1] << 8) + characters[0];

	return number;
}