#include "ServerSocket.h"
#include "SocketException.h"
#include <pthread.h>
#include <iostream>

list<Socket*>ServerSocket::clientSockets;
ThreadReadWriteLock ServerSocket::readWriteLock;
bool  ServerSocket::serviceFlag = true;

ServerSocket::ServerSocket(const int port)
{
    if( ! Socket::Create() ){
        throw SocketException("Could not create server socket");
    }

    if( ! Socket::Bind(port) ){
        throw SocketException("Could not bind to port");
    }

    if( ! Socket::Listen()){
        throw SocketException("Could not listen to socket");
    }
}

ServerSocket::~ServerSocket()
{
    list<Socket*>::iterator iter;
    for(iter = clientSockets.begin(); iter != clientSockets.end(); iter++){
       delete(*iter);
    }
}

void ServerSocket::Accept(Socket& socket)
{
     if( ! Socket::Accept( socket )){
         throw SocketException("Could not accept socket");
     }
}


bool ServerSocket::Accept()
{
     Socket *clientSocket = new Socket;
     Accept(*clientSocket);
     AddClient(clientSocket);

     pthread_t newThread;
     int result = pthread_create(&newThread,NULL,ProcessMessage,static_cast<void *>(clientSocket));
     if(result != 0){
       return false;
     }

     result = pthread_detach(newThread);
     if(result != 0){
       std::cout << "pthread_detach failed\n";
     }

     return true;
}

void ServerSocket::Run()
{
  while(serviceFlag){
     if(clientSockets.size() >= static_cast<unsigned int>(MAXCONNECTION)){
        serviceFlag = false;
     }else{
        serviceFlag = Accept();
     }//end if else
     sleep(1);
  }
}

void *ServerSocket::ProcessMessage(void *arg)
{
    std::string message;
    Socket *clientSocket = static_cast<Socket *>(arg);
    clientSocket->Send(*clientSocket,"Welcome!  I am server");

    while(serviceFlag){
       clientSocket->Receive(*clientSocket,message);
       if(message == "exit" || message == ""){
          clientSocket->Send(*clientSocket,"exit");
          DeleteClient(clientSocket);
          break;
       }else{
         // std::cout <<"Receive" << clientSocket->GetAddress() << ":" << message << std::endl;
          SendMsgToAllUsers(message);
       }//end if else
       message.clear();
       sleep(1);
    }
    pthread_exit(NULL);
    return NULL;
}

void ServerSocket::AddClient(Socket *socket)
{
     if(readWriteLock.SetWriteLock()){
        clientSockets.push_back(socket);
        std::cout << "Now " << clientSockets.size() << "uses..";
        std::cout << "New User:" << socket->GetAddress() <<" " <<socket->GetPort()<<"\n";
        readWriteLock.UnLock();
     }else{
        serviceFlag = false;
     }//end if else

}

void ServerSocket::DeleteClient(Socket *socket)
{
     if(readWriteLock.SetWriteLock()){
         list<Socket*>::iterator iter;
         for(iter = clientSockets.begin();iter!=clientSockets.end();iter++){
             if((*iter)->GetAddress() == socket->GetAddress()
                && (*iter)->GetPort() == socket->GetPort()){
                   delete(*iter);
                   clientSockets.erase(iter);
                   std::cout << "Now " << clientSockets.size() << "users..\n";
                   break;
             }
         }
         readWriteLock.UnLock();
     }else{
         serviceFlag = false;
     }
}
void  ServerSocket::SendMsgToAllUsers(const std::string& message)
{

    list<Socket*>::iterator iter;
    for(iter = clientSockets.begin(); iter != clientSockets.end(); iter++){
          (*iter)->Send(*(*iter),message);
    }
}




































