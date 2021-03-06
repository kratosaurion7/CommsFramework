#pragma once

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <iostream>
#include <cstdarg>
#include <ctime>
#include <string>
#include <list>

#include "Network.h"

#include "Collections/BaseList.h"
#include "Collections/BaseQueue.h"

#define DEFAULT_BUFLEN 512

class SocketClient;

struct RECEIVE_DATA_ARGS {
    SocketClient* Instance;
};

class SocketClient
{
public:
    std::string ClientName;
    std::string ServerAddress;
    std::string ServerPort;

    SocketClient(std::string serverAddress, std::string portNumber);
    ~SocketClient();

    void Init();

    void Connect();

    int SendByte(char data);
    int SendWord(unsigned short data);
    int SendDWord(unsigned int data);
    int SendQWord(unsigned long data);

    int SendData(char* data, int length);
    int SendData(std::string data);

    char* PeekData(int &size);
    char* PopData(int &size);
    bool HasData();

    void ReceiveData();
    void StartReceiveData();
    
    void Disconnect();

    void Close();
    
    void PrintInfo(char* formatStr, ...);
private:
    WSADATA wsaData;

    SOCKET ConnectSocket;

    HANDLE readThread;

    BaseQueue<NetworkMessage*>* data;

    static DWORD WINAPI ClientReceiveFunc(LPVOID lpParam);
    
    bool StopSocket;

    void StopReceiving();

    struct addrinfo *result = NULL,
        *ptr = NULL,
        hints;


};

#endif