#include "SocketClient.h"



SocketClient::SocketClient(std::string serverAddress)
{
    ServerAddress = serverAddress;

    ConnectSocket = INVALID_SOCKET;

    StopSocket = false;

    this->data = new std::list<std::string>();
}


SocketClient::~SocketClient()
{
}

void SocketClient::Init()
{
    int res = 0;

    res = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (res != 0)
    {
        DWORD err = GetLastError();

        PrintInfo("WinSock Startup error %d", res);

        return;
    }

    PrintInfo("WinSock Startup success !");

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    res = getaddrinfo(ServerAddress.c_str(), "27015", &hints, &result);

    if (res != 0)
    {
        DWORD err = GetLastError();

        WSACleanup();

        PrintInfo("WinSock GetAddrInfo error %d", res);

        return;
    }

    PrintInfo("WinSock GetAddrInfo success !");

    ptr = result;

    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        res = WSAGetLastError();

        PrintInfo("Error at socket() %ld", res);

        freeaddrinfo(result);
        WSACleanup();

        return;
    }

}

void SocketClient::Connect()
{
    int res = 0;

    res = connect(ConnectSocket, ptr->ai_addr, ptr->ai_addrlen);

    if (res == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket == INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        PrintInfo("Cannot connect to server.");
        WSACleanup();

        return;
    }

    StopSocket = false;

    StartReceiveData();
}

void SocketClient::SendData(std::string data)
{
    int res = 0;
    int receiveBufLen = DEFAULT_BUFLEN;
    const char* sendBuf = data.c_str();
    char recvBuf[DEFAULT_BUFLEN];

    res = send(ConnectSocket, sendBuf, strlen(sendBuf), 0);

    if (res == SOCKET_ERROR)
    {
        PrintInfo("Send data failed %ld", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();

        return;
    }

    PrintInfo("Sent %d bytes", res);
}

void SocketClient::Disconnect()
{
    int res = 0;
    
    res = shutdown(ConnectSocket, SD_SEND);

    if (res == SOCKET_ERROR)
    {
        PrintInfo("Shutdown failed %ld !", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();

        return;
    }
}

void SocketClient::Close()
{
    closesocket(ConnectSocket);
    WSACleanup();
}

void SocketClient::PrintInfo(char* formatStr, ...)
{
    DWORD wait = WaitForSingleObject(outMut, 200);

    va_list args;
    printf("[%s] ", this->ClientName.c_str());
    va_start(args, formatStr);
    vprintf(formatStr, args);
    va_end(args);
    printf("\n");

    ReleaseMutex(outMut);
}

DWORD WINAPI SocketClient::ClientReceiveFunc(LPVOID lpParam)
{
    RECEIVE_DATA_ARGS* recArgs = (RECEIVE_DATA_ARGS*)lpParam;

    while (true)
    {
        if (recArgs->Instance->StopSocket)
            return 0;

        recArgs->Instance->ReceiveData();
    }

    return 0;
}

void SocketClient::ReceiveData()
{
    int res = 0;

    char* recvBuf = new char[DEFAULT_BUFLEN];
    int receiveBufLen = DEFAULT_BUFLEN;

    res = recv(ConnectSocket, recvBuf, receiveBufLen, 0);
    if (res > 0)
    {
        PrintInfo("Bytes received: %d", res);

        this->data->push_back(recvBuf);
    }
    else if (res == 0)
    {
        PrintInfo("Connection closed");
    }
    else
    {
        PrintInfo("recv failed: %d", WSAGetLastError());
    }
}

void SocketClient::StartReceiveData()
{
    RECEIVE_DATA_ARGS* args = new RECEIVE_DATA_ARGS();
    args->Instance = this;

    DWORD threadId;

    HANDLE threadHandle = CreateThread(NULL, 0, ClientReceiveFunc, args, 0, &threadId);

    readThread = threadHandle;
}

void SocketClient::StopReceiving()
{
    StopSocket = true;
}