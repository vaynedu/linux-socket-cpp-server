#include "ClientSocket.h"
#include "SocketException.h"

ClientSocket::ClientSocket(const std::string& host,const int port)
{
    if( ! Socket::Create() ){
        throw SocketException("Could not create client socket");
    }//end if

    if( ! Socket::Connect(host,port)){
        throw SocketException("Could not connect to port");
    }
}

ClientSocket::~ClientSocket()
{

}

bool ClientSocket::Send(const std::string& message)
{
    return Socket::Send(static_cast<Socket&>(*this),message);
}

int ClientSocket::Receive(std::string& message)
{
    return Socket::Receive(static_cast<Socket&>(*this),message);
}
