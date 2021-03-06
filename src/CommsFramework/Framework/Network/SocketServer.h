#pragma once

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <string>
#include <list>

#include "Network.h"
#include "Collections/BaseList.h"
#include "Collections/BaseQueue.h"

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

    void SendToSocket(SOCKET clientSocket, std::string data);

    void Stop();

    void Close();

    HANDLE GetServerThread();

    void SocketServer::PrintInfo(char* formatStr, ...);
private:
    WSADATA wsaData;

    HANDLE serverListenThread;

    int clientThreadCount = 0;
    BaseList<HANDLE>* clientThreads;

    BaseQueue<NetworkMessage*>* messages;

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

#endif