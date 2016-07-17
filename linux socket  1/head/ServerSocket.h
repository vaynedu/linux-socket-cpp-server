#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "Socket.h"

class ServerSocket:public Socket
{
    public:
        ServerSocket(const int port);
        ServerSocket();
        virtual ~ServerSocket();

        void Accept(Socket& socket);
};


#endif
