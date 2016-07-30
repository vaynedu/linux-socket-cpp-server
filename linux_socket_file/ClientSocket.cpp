#include <iostream>
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

void ClientSocket::SendFile(const std::string&  fileName)
{
    FileOperator    fileOperator;
    fileOperator.Open(fileName.c_str(),"rb");
    std:: string buffer;

    int readBytes;
   // Send("File");

    while((readBytes = fileOperator.ReadFromFile(buffer)) > 0){
        if(Send(buffer) < 0){
            std :: cout << "Send failed\n";
            break;
        }
    }
}
