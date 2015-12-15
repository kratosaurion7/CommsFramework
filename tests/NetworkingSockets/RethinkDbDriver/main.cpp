#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define test_CLIENT
//#define test_SERVER

#define PORT_NB "27077"

#include "SocketServer.h"
#include "SocketClient.h"

#include "RethinkDb.h"

#include "Utils.h"

DWORD WINAPI ServerListenFunc(LPVOID lpParam);

DWORD WINAPI ServerListenFunc(LPVOID lpParam)
{
    SocketServer* serv = new SocketServer(PORT_NB);
    serv->ServerName = "ServerOne";

    serv->Init();

    while (true)
    {
        serv->ListenAndAccept();
    }
    
    return 0;
}


int main()
{
    outMut = CreateMutex(NULL, FALSE, NULL);

    int res = 0;

    DWORD threadId;

    HANDLE serverThread = CreateThread(NULL, 0, ServerListenFunc, NULL, 0, &threadId);

    //RethinkDb* db = new RethinkDb();

    //db->Connect();
    //
    //while (true)
    //{
    //    db->Update();
    //}

    //return 0;

#ifdef test_CLIENT

    SocketClient* cli = new SocketClient("127.0.0.1", PORT_NB);
    cli->ClientName = "OneClient";
    cli->Init();
    cli->Connect();

    SocketClient* cli2 = new SocketClient("127.0.0.1", PORT_NB);
    cli2->ClientName = "TwoClient";
    cli2->Init();
    cli2->Connect();

    cli->SendWord('F');

    while (true)
    {
        cli->SendData("Hello World");
        cli2->SendData("Hello Space");

        Sleep(5000);
    }


    cli->Disconnect();
    cli->Close();

    cli2->Disconnect();
    cli2->Close();

    return 0;
#endif

#ifdef test_SERVER

    SocketServer* serv = new SocketServer();

    serv->Init();

    serv->StartManaged();

    HANDLE handel = serv->GetServerThread();
    WaitForSingleObject(handel, 30000);

    return 0;
    // TEst STuff


    WSADATA wsaData;

    res = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (res != 0)
    {
        DWORD err = GetLastError();

        printf("WinSock Startup error %d\n", res);

        return 1;
    }

    printf("WinSock Startup success !\n");

#endif
    // CLIENT INIT
#ifdef test_CLIENT

    // SETUP SERVER INFO

    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    res = getaddrinfo("127.0.0.1", "27015", &hints, &result);

    if (res != 0)
    {
        DWORD err = GetLastError();

        WSACleanup();

        printf("WinSock GetAddrInfo error %d", res);

        return 1;
    }

    printf("WinSock GetAddrInfo success !\n");

    // CREATE SOCKET

    SOCKET ConnectSocket = INVALID_SOCKET;
    
    ptr = result;

    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        res = WSAGetLastError();

        printf("Error at socket() %ld\n", res);

        freeaddrinfo(result);
        WSACleanup();

        return 1;
    }

    // CONNECT TO SERVER

    res = connect(ConnectSocket, ptr->ai_addr, ptr->ai_addrlen);

    if (res == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);
    // TODO : Try next ?

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Cannot connect to server.\n");
        WSACleanup();

        return 1;
    }
    
    // SEND DATA
#define DEFAULT_BUFLEN 512

    int receiveBufLen = DEFAULT_BUFLEN;
    char* sendBuf = "Ping";
    char recvBuf[DEFAULT_BUFLEN];

    res = send(ConnectSocket, sendBuf, strlen(sendBuf), 0);
    
    if (res == SOCKET_ERROR)
    {
        printf("Send data failed %ld\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();

        return 1;
    }

    printf("Sent %d bytes\n", res);

    res = shutdown(ConnectSocket, SD_SEND);

    if (res == SOCKET_ERROR)
    {
        printf("Shutdown failed %ld !\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        
        return 1;
    }

    do {
        res = recv(ConnectSocket, recvBuf, receiveBufLen, 0);
        if (res > 0)
            printf("Bytes received: %d\n", res);
        else if (res == 0)
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());
    } while (res > 0);

    closesocket(ConnectSocket);
    WSACleanup();

    //return 0;

#endif

#ifdef test_SERVER

#define DEFAULT_BUFLEN 512

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    res = getaddrinfo(NULL, "27015", &hints, &result);
    if (res != 0) {
        printf("getaddrinfo failed with error: %d\n", res);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    res = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (res == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    res = listen(ListenSocket, SOMAXCONN);
    if (res == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {
        res = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (res > 0) {
            printf("Bytes received: %d\n", res);

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, res, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (res == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (res > 0);

    // shutdown the connection since we're done
    res = shutdown(ClientSocket, SD_SEND);
    if (res == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;


#endif



    char buf[256];
    scanf("%s", buf);

    printf("%s", buf);
    return 0;
}