#ifndef  SOCKET_H
#define  SOCKET_H

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

const int MAXCONNECTION = 5;
const int MAXRECEIVE = 500;

class Socket
{
    private:
        int m_sockfd;
        struct sockaddr_in m_address;

    public:
        Socket();

        bool Create();
        bool Bind(const int port);
        bool Listen()const;
        bool Accept(Socket& clientSocket)const;

        bool Connect(const std::string& host,const int port);
        //data transmission
        bool Send(Socket& socket,const std::string& message)const;
        int  Receive(Socket& socket,std::string& message)const;

        void SetNonBlocking(const bool flag);
        bool IsValid()const;
        char *  GetAddress();
        int  GetPort();
        int  GetSocketfd();

        virtual ~Socket();

};

#endif
