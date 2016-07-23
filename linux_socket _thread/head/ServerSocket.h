#ifndef  SERVERSOCKET_H
#define  SERVERSOCKET_H

#include "Socket.h"
#include <list>
#include <semaphore.h>
#include "ThreadReadWriteLock.h"

using std::list;

class ServerSocket:public Socket
{
    public:
        ServerSocket(const int port);
        ServerSocket();
        virtual ~ServerSocket();

        void Accept(Socket& socket);
        //run server to connect multi-clients
        void Run();
    private:
        //accept multi-clients
        bool Accept();
        void AddClient(Socket *clientSocket);
        static void  DeleteClient(Socket *clientSocket);
        static void *ProcessMessage(void *arg);
        static void SendMsgToAllUsers(const std::string& message);

        static list<Socket *>clientSockets;
        static bool serviceFlag;
         //use thread-read-write-lock to synchronize threads
        static ThreadReadWriteLock readWriteLock;
};



#endif
