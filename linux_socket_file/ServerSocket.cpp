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


void ServerSocket::RecvFile(Socket* clientSocket)
{
    int recvBytes;
    int writeBytes;
    int port = clientSocket->GetPort();
    char  portbuf[20];
    std::string message;
    FileOperator  fileOperator;
    std::string fileaddress = clientSocket->GetAddress();
    sprintf(portbuf,"%d",port);
    std::string fileport = portbuf;
    std::string filename = fileaddress + fileport;

    fileOperator.Open(filename.c_str(),WRITE_CREATE_MODE);

    while((recvBytes = Socket::Receive(*clientSocket,message)) > 0){
      std::cout << "message length : "<< message.size() << "\n";
      writeBytes = fileOperator.WriteToFile(message);
      std::cout << "writeBytes: " << writeBytes <<"\n";


      if(writeBytes < recvBytes){
        std::cout << "write to file failed\n";
        Socket::Send(*clientSocket,"Error when server receiveing file.");
        return ;
      }
      if(recvBytes == 0 || recvBytes != MAXRECEIVE){
         break;
      }
    }

    if(recvBytes >= 0){
      Socket::Send(*clientSocket,"server has received your file");
    }
}
