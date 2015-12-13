#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")


#include <string>
#include <list>

#include "BaseList.h"
#include "Utils.h"

#define MAX_SOCK_CLIENTS 5
#define DEFAULT_BUFLEN 512
#define MAX_THREADS 10

class SocketServer;

struct SOCKET_READ_ARGS {
    SOCKET targetSocket;

    SocketServer* Instance;
};

struct SERVER_LISTEN_ARGS {
    SocketServer* Instance;
};

class SocketServer
{
public:
    std::string ServerName;
    std::string ServerPort;

    SocketServer(std::string portNumber);
    ~SocketServer();

    void Init();

    void Start();

    void StartManaged();

    void ListenAndAccept();

    void ReadFromSocket(SOCKET clientSocket);

    void Stop();

    void Close();

    HANDLE GetServerThread();

    void SocketServer::PrintInfo(char* formatStr, ...);
private:
    WSADATA wsaData;

    HANDLE serverListenThread;

    int clientThreadCount = 0;
    BaseList<HANDLE>* clientThreads;

    BaseList<std::string>* messages;

    static DWORD WINAPI ServerListenFunc(LPVOID lpParam);
    void StartListeningAndAccept();

    static DWORD WINAPI ReadFromSocketFunc(LPVOID lpParam);
    void StartReadingFromSocket(SOCKET clientSocket);

    void StopReadingFromSocket(SOCKET clientSocket);

    bool serverValid = true;

    SOCKET ListenSocket;

    BaseList<SOCKET>* ClientSockets;
    
    struct addrinfo *result = NULL;
    struct addrinfo hints;
};