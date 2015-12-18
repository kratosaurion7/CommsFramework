#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")


#include <string>

int StartNetworkComponent(LPWSADATA outData);
void StopNetworkComponent();

struct NetworkMessage {
    __int64 TimeStamp;

    std::string Message;
};

int StartNetworkComponent(LPWSADATA outData)
{
    int result = WSAStartup(MAKEWORD(2, 2), outData);

    return result;
};

void StopNetworkComponent()
{
    WSACleanup();
};