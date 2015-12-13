#pragma once

#include "BaseList.h"
#include "PointerList.h"
#include "SocketClient.h"

class RethinkDb
{
public:
    enum RETHINKDB_STATE
    {
        STOPPED,
        HANDSHAKE,

    };

    struct RETHINKDB_HANDSHAKE
    {
        enum STATE
        {
            STOPPED,
            SEND_VERSION,   // 4 bytes
            SEND_KEY_SIZE,  // 4 bytes
            SEND_KEY,       // n bytes
            SEND_PROTOCOL,  // 4 bytes
            RECEIVE_SUCCESS // 7 bytes
        };
    };

    RETHINKDB_STATE ClientState;
    RETHINKDB_HANDSHAKE::STATE HandshakeState;

    bool driverError = false;

    RethinkDb();
    ~RethinkDb();

    void Update();

    void Execute_Handshake();

private:
    // Server = 104.236.223.173:28015
    SocketClient* sock;
};

