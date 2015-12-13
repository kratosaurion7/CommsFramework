#include "RethinkDb.h"



RethinkDb::RethinkDb()
{
    this->sock = new SocketClient("104.236.223.173", "28015");

    this->ClientState = STOPPED;
    this->HandshakeState = RETHINKDB_HANDSHAKE::STOPPED;
}


RethinkDb::~RethinkDb()
{
    delete(sock);
}

void RethinkDb::Update()
{
    if (driverError == true)
        return;

    if (this->sock->HasData())
    {
        int dataLength = 0;
        char* messageData = sock->PeekData(dataLength);

        printf("%s", messageData);
    }

    switch (this->ClientState)
    {
        case HANDSHAKE:
        {
            this->Execute_Handshake();

            break;
        }
        default:
            break;
    }
}

void RethinkDb::Connect()
{
    this->ClientState = HANDSHAKE;

    this->sock->Init();

    this->sock->Connect();
}

void RethinkDb::Execute_Handshake()
{
    switch (this->HandshakeState)
    {
        case RETHINKDB_HANDSHAKE::STOPPED:
        {
            this->HandshakeState = RETHINKDB_HANDSHAKE::SEND_VERSION;

            break;
        }
        case RETHINKDB_HANDSHAKE::SEND_VERSION:
        {
            //char* data = new char[4];
            //data[0] = 0x20;
            //data[1] = 0x2d;
            //data[2] = 0x0c;
            //data[3] = 0x40;

            int ret = sock->SendData("\x20\x2d\x0c\x40", 4);

            if (ret == -1)
            {
                driverError = true;

                return;
            }

            this->HandshakeState = RETHINKDB_HANDSHAKE::SEND_KEY_SIZE;

            break;
        }
        case RETHINKDB_HANDSHAKE::SEND_KEY_SIZE:
        {
            // Send Key
            int ret = sock->SendData("\x00", 4);

            if (ret == -1)
            {
                driverError = true;

                return;
            }

            this->HandshakeState = RETHINKDB_HANDSHAKE::SEND_KEY;

            break;
        }
        case RETHINKDB_HANDSHAKE::SEND_KEY:
        {
            // Skip step since no auth key

            this->HandshakeState = RETHINKDB_HANDSHAKE::SEND_PROTOCOL;

            break;
        }
        case RETHINKDB_HANDSHAKE::SEND_PROTOCOL:
        {
            int ret = sock->SendData("\xc7\x70\x69\x7e", 4);

            if (ret == -1)
            {
                driverError = true;

                return;
            }

            this->HandshakeState = RETHINKDB_HANDSHAKE::RECEIVE_SUCCESS;

            break;
        }
        case RETHINKDB_HANDSHAKE::RECEIVE_SUCCESS:
        {
            if (sock->HasData())
            {
                int dataSize = 0;
                char* result = sock->PopData(dataSize);

                if (strncmp(result, "SUCCESS", dataSize) == 0)
                {
                    this->ClientState = STOPPED;

                    HandshakeComplete = true;


                }
            }

            break;
        }

        default:
            break;
    }
}
