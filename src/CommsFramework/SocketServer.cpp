#include "SocketServer.h"



SocketServer::SocketServer(std::string portNumber)
{
    ServerPort = portNumber;

    messages = new BaseQueue<NetworkMessage*>();

    clientThreads = new BaseList<HANDLE>();
    ClientSockets = new BaseList<SOCKET>();

    //for (int i = 0; i < MAX_SOCK_CLIENTS;i++)
    //{
    //    ClientSockets[i] = INVALID_SOCKET;
    //}

}


SocketServer::~SocketServer()
{
    messages->Clear();

    delete(messages);
}

void SocketServer::Init()
{
    int res = 0;

    res = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (res != 0)
    {
        DWORD err = GetLastError();

        PrintInfo("WinSock Startup error %d", res);

        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    res = getaddrinfo(NULL, ServerPort.c_str(), &hints, &result);
    if (res != 0) {
        PrintInfo("getaddrinfo failed with error: %d", res);
        WSACleanup();

        serverValid = false;

        return;
    }

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        PrintInfo("socket failed with error: %ld", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        
        serverValid = false;

        return;
    }

    res = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (res == SOCKET_ERROR) {
        PrintInfo("bind failed with error: %d", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        
        serverValid = false;

        return;
    }

    freeaddrinfo(result);
}

void SocketServer::Start()
{
    while (true)
    {
        ListenAndAccept();
    }
}

void SocketServer::StartManaged()
{
    StartListeningAndAccept();
}

void SocketServer::Stop()
{
    auto it = this->ClientSockets->GetContainer()->begin();
    while (it != this->ClientSockets->GetContainer()->end())
    {
        SOCKET item = (*it);

        StopReadingFromSocket(item);

        it++;
    }
}

void SocketServer::Close()
{
    Stop();

    WSACleanup();
}

HANDLE SocketServer::GetServerThread()
{
    return this->serverListenThread;
}

void SocketServer::PrintInfo(char* formatStr, ...)
{
    DWORD wait = WaitForSingleObject(outMut, 200);

    va_list args;
    printf("[%s] ", this->ServerName.c_str());
    va_start(args, formatStr);
    vprintf(formatStr, args);
    va_end(args);
    printf("\n");

    ReleaseMutex(outMut);
}

DWORD WINAPI SocketServer::ServerListenFunc(LPVOID lpParam)
{
    SERVER_LISTEN_ARGS* listenArg = (SERVER_LISTEN_ARGS*)lpParam;

    while (true)
    {
        listenArg->Instance->ListenAndAccept();
    }

    return 0;
}

void SocketServer::StartListeningAndAccept()
{
    SERVER_LISTEN_ARGS* args = new SERVER_LISTEN_ARGS();
    args->Instance = this;
    
    DWORD threadId;

    HANDLE threadHandle = CreateThread(NULL, 0, ServerListenFunc, args, 0, &threadId);

    this->serverListenThread = threadHandle;
}

void SocketServer::ListenAndAccept()
{
    int res = 0;

    res = listen(ListenSocket, SOMAXCONN);
    if (res == SOCKET_ERROR) {
        int err = WSAGetLastError();

        PrintInfo("listen failed with error: %d", err);
        closesocket(ListenSocket);
        WSACleanup();

        return;
    }

    SOCKET currentClientSocket = INVALID_SOCKET;

    currentClientSocket = accept(ListenSocket, NULL, NULL);
    if (currentClientSocket == INVALID_SOCKET) {
        PrintInfo("accept failed with error: %d", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();

        return;
    }

    StartReadingFromSocket(currentClientSocket);
}

DWORD SocketServer::ReadFromSocketFunc(LPVOID lpParam)
{
    SOCKET_READ_ARGS* socketArg = (SOCKET_READ_ARGS*)lpParam;

    while (true)
    {
        socketArg->Instance->ReadFromSocket(socketArg->targetSocket);
    }

    return 0;
}

void SocketServer::StartReadingFromSocket(SOCKET clientSocket)
{
    SOCKET_READ_ARGS* args = new SOCKET_READ_ARGS();
    args->Instance = this;
    args->targetSocket = clientSocket;

    DWORD threadId;

    HANDLE threadHandle = CreateThread(NULL, 0, ReadFromSocketFunc, args, 0, &threadId);

    clientThreads->Add(threadHandle);
}

void SocketServer::ReadFromSocket(SOCKET clientSocket)
{
    int res;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    do {
        res = recv(clientSocket, recvbuf, recvbuflen, 0);
        if (res > 0) {
            PrintInfo("Bytes received: %d", res);

            NetworkMessage* msg = new NetworkMessage();
            msg->Message = recvbuf;
            msg->TimeStamp = time(NULL);
            
            messages->Push(msg);

            // Echo the buffer back to the sender
            res = send(clientSocket, recvbuf, res, 0);
            if (res == SOCKET_ERROR) {
                PrintInfo("send failed with error: %d", WSAGetLastError());
                closesocket(clientSocket);
                WSACleanup();

                return;
            }
            PrintInfo("Bytes sent: %d", res);
        }
        else if (res == 0)
            PrintInfo("Connection closing...");
        else {
            PrintInfo("recv failed with error: %d", WSAGetLastError());
            closesocket(clientSocket);
            WSACleanup();

            return;
        }

    } while (res > 0);

}

void SocketServer::StopReadingFromSocket(SOCKET clientSocket)
{
    if (clientSocket != INVALID_SOCKET)
    {
        int result = shutdown(clientSocket, SD_SEND);

        if (result == SOCKET_ERROR)
        {
            int error = WSAGetLastError();

            PrintInfo("Shutdown failed for socket. Err : %d", error);

            closesocket(clientSocket);
        }
    }
}