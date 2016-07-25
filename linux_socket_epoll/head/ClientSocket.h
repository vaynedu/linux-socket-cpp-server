#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "Socket.h"
#include <string.h>

class ClientSocket:public Socket
{
    public:
        ClientSocket(const std::string& host,const int port);
        virtual ~ClientSocket();

        bool Send(const std::string& message);
        int Receive(std::string& message);
};

#endif