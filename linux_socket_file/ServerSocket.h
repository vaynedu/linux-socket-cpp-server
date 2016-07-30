#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "Socket.h"
#include "FileOperator.h"
#include <iostream>
#include <string>
#include <string.h>


class ServerSocket:public Socket
{
    public:
        ServerSocket(const int port);
        ServerSocket();
        virtual ~ServerSocket();

        void Accept(Socket& socket);
        void RecvFile(Socket* clientSocket);
};


#endif
