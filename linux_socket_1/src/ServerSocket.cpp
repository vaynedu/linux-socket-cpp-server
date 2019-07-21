#include "ServerSocket.h"
#include "SocketException.h"

ServerSocket::ServerSocket(const int port)
{
  if( ! Socket::Create() ){
    throw SocketException("Could not create server socket.");
  }//end if

  if( ! Socket::Bind(port) ){
    throw SocketException("Could not bind to port.");
  }//end if

  if( ! Socket::Listen() ){
    throw SocketException("Could not listen to socket.");
  }//end if

}

ServerSocket::~ServerSocket()
{

}

void ServerSocket::Accept(Socket& socket)
{
  if( ! Socket::Accept(socket)){
    throw SocketException("Could not accept socket.");
  }//end if
}
