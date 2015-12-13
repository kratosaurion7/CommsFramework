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
            int ret = sock->SendData("V_04");

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
            int ret = sock->SendDWord(0);

            if (ret == -1)
            {
                driverError = true;

                return;
            }

            this->HandshakeState = RETHINKDB_HANDSHAKE::SEND_KEY_SIZE;

            break;
        }
        case RETHINKDB_HANDSHAKE::SEND_KEY:
        {
            // Skip step since no auth key

            this->HandshakeState = RETHINKDB_HANDSHAKE::SEND_KEY;

            break;
        }
        case RETHINKDB_HANDSHAKE::SEND_PROTOCOL:
        {
            int ret = sock->SendDWord(0x7e6970c7);

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
            

            break;
        }

        default:
            break;
    }
}
