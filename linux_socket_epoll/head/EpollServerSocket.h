#ifndef   EPOLLSERVERSOCKET_H
#define   EPOLLSERVERSOCKET_H

#include "Socket.h"
#include "Epoll.h"
#include <map>

class EpollServerSocket:public Socket
{
     public:
        EpollServerSocket(const int port);
        virtual ~EpollServerSocket();
        void Run();

     private:
         //when using the EPOLLET flag,
        //need to continuously read/write a file descriptor until EAGAIN,
        //so we write these two functions for read/write
        void SendMessage(Socket& clientSocket,const std::string& message) const;
        void ReceiveMessage(Socket& clientSocket,std::string& message);

        void ProcessMessage(Socket& clientSocket);
        void SendToAllUsers(const std::string& message)const;
        //add event to epoll
        bool AddNewClient(Socket& clientSocket);
        //delete client from map clientSockets
        void DeleteClient(int sockfd);
        std::map<int,Socket*>clientSockets;
        Epoll epoll;
};


#endif
