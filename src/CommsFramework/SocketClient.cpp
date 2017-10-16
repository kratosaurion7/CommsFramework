#include "SocketClient.h"

#ifdef WIN32

SocketClient::SocketClient(std::string serverAddress, std::string portNumber)
{
    ServerAddress = serverAddress;
    ServerPort = portNumber;

    ConnectSocket = INVALID_SOCKET;

    StopSocket = false;

    this->data = new BaseQueue<NetworkMessage*>();
}


SocketClient::~SocketClient()
{
}

void SocketClient::Init()
{
    int res = 0;

    res = StartNetworkComponent(&wsaData);

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

    res = getaddrinfo(ServerAddress.c_str(), ServerPort.c_str(), &hints, &result);

    if (res != 0)
    {
        DWORD err = GetLastError();

        //WSACleanup();

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
        //WSACleanup();

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
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        PrintInfo("Cannot connect to server.");
        //WSACleanup();

        return;
    }

    StopSocket = false;

    StartReceiveData();
}

int SocketClient::SendByte(char data)
{
    int res = 0;

    res = send(ConnectSocket, &data, 1, 0);

    if (res == SOCKET_ERROR)
    {
        PrintInfo("Send data failed %ld", WSAGetLastError());
        closesocket(ConnectSocket);
        //WSACleanup();

        return res;
    }

    PrintInfo("Sent %d bytes", res);

    return res;
}

int SocketClient::SendWord(unsigned short data)
{
    int res = 0;

    char bytes = (char)data;

    res = send(ConnectSocket, &bytes, 2, 0);

    if (res == SOCKET_ERROR)
    {
        PrintInfo("Send data failed %ld", WSAGetLastError());
        closesocket(ConnectSocket);
        //WSACleanup();

        return res;
    }

    PrintInfo("Sent %d bytes", res);

    return res;
}

int SocketClient::SendDWord(unsigned int data)
{
    int res = 0;

    char bytes = (char)data;

    res = send(ConnectSocket, &bytes, 4, 0);

    if (res == SOCKET_ERROR)
    {
        PrintInfo("Send data failed %ld", WSAGetLastError());
        closesocket(ConnectSocket);
        //WSACleanup();

        return res;
    }

    PrintInfo("Sent %d bytes", res);

    return res;
}

int SocketClient::SendQWord(unsigned long data)
{
    int res = 0;

    char bytes = (char)data;

    res = send(ConnectSocket, &bytes, 8, 0);

    if (res == SOCKET_ERROR)
    {
        PrintInfo("Send data failed %ld", WSAGetLastError());
        closesocket(ConnectSocket);
        //WSACleanup();

        return res;
    }

    PrintInfo("Sent %d bytes", res);

    return res;
}

int SocketClient::SendData(char * data, int length)
{
    int res = 0;
    const char* sendBuf = data;

    res = send(ConnectSocket, sendBuf, length, 0);

    if (res == SOCKET_ERROR)
    {
        PrintInfo("Send data failed %ld", WSAGetLastError());
        closesocket(ConnectSocket);
        //WSACleanup();

        return res;
    }

    PrintInfo("Sent %d bytes", res);

    return res;
}

int SocketClient::SendData(std::string data)
{
    int res = 0;
    int receiveBufLen = DEFAULT_BUFLEN;
    const char* sendBuf = data.c_str();

    res = send(ConnectSocket, sendBuf, strlen(sendBuf), 0);

    if (res == SOCKET_ERROR)
    {
        PrintInfo("Send data failed %ld", WSAGetLastError());
        closesocket(ConnectSocket);
        //WSACleanup();

        return res;
    }

    PrintInfo("Sent %d bytes", res);

    return res;
}

char* SocketClient::PeekData(int & size)
{
    if (this->data->Count() > 0)
    {
        std::string data = this->data->Peek()->Message;

        std::string* outData = new std::string(data.data());

        size = outData->size();

        return (char*)outData->data();
    }

    return NULL;
}

char* SocketClient::PopData(int &size)
{
    if (this->data->Count() > 0)
    {
        std::string data = this->data->Pop()->Message;

        std::string* outData = new std::string(data.data());

        size = outData->size();

        return (char*)outData->data();
    }

    return NULL;
}

bool SocketClient::HasData()
{
    return this->data->Count() > 0;
}

void SocketClient::Disconnect()
{
    int res = 0;
    
    res = shutdown(ConnectSocket, SD_SEND);

    if (res == SOCKET_ERROR)
    {
        PrintInfo("Shutdown failed %ld !", WSAGetLastError());
        closesocket(ConnectSocket);
        //WSACleanup();

        return;
    }
}

void SocketClient::Close()
{
    closesocket(ConnectSocket);
    //WSACleanup();
}

void SocketClient::PrintInfo(char* formatStr, ...)
{
    //DWORD wait = WaitForSingleObject(outMut, 200);

    va_list args;
    printf("[%s] ", this->ClientName.c_str());
    va_start(args, formatStr);
    vprintf(formatStr, args);
    va_end(args);
    printf("\n");

    //ReleaseMutex(outMut);
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

        NetworkMessage* msg = new NetworkMessage();
        msg->TimeStamp = time(NULL);
        msg->Message = recvBuf;

        this->data->Push(msg);
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

#endif