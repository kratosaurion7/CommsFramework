#include "Network.h"

#ifdef WIN32

int StartNetworkComponent(LPWSADATA outData)
{
	int result = WSAStartup(MAKEWORD(2, 2), outData);

	return result;
};

void StopNetworkComponent()
{
	WSACleanup();
};

#endif