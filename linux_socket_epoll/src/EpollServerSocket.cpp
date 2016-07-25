#include "EpollServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <errno.h>
#include <stdio.h>


EpollServerSocket::EpollServerSocket(const int port)
{
    if( ! Socket::Create()){
        throw SocketException(" could not create server socket");
    }

    if( ! Socket::Bind(port)){
        throw SocketException(" could not bind to port");
    }

    if( ! Socket::Listen()){
        throw SocketException(" could not listen to socket");
    }

    Socket::SetNonBlocking(true);
}

EpollServerSocket::~EpollServerSocket()
{
   std::map<int,Socket*>::iterator iter;
   for(iter = clientSockets.begin();iter!= clientSockets.end();iter++){
      delete iter->second;
   }
}

void EpollServerSocket::Run()
{
    int i;
    int eventNumber;
    Socket *clientSocket;
    //add listener socketfd to epoll
    if(epoll.Add(Socket::GetSocketfd(),EPOLLIN) == false){
        return ;
    }
    while(true){
        eventNumber = epoll.Wait();
        for(i = 0; i < eventNumber; i++){
            if((epoll.GetEvents(i) & EPOLLERR)  ||
                epoll.GetEvents(i) & EPOLLHUP   ||
             (!(epoll.GetEvents(i) & EPOLLIN))){
                std::cout << "epoll error\n";
                DeleteClient(epoll.GetEventOccurfd(i));
                continue;
            }else if(epoll.GetEventOccurfd(i) == Socket::GetSocketfd()){
                  clientSocket = new Socket();
                  if(AddNewClient(*clientSocket) == false){
                       return ;
                  }//end if
                  clientSockets[clientSocket->GetSocketfd()] = clientSocket;
            }else{
                 clientSocket = clientSockets[epoll.GetEventOccurfd(i)];
                 ProcessMessage(*clientSocket);
            }//end if else 

        }//end for
    }//end while
}
void EpollServerSocket::ProcessMessage(Socket& clientSocket)
{
     std::string message;
     ReceiveMessage(clientSocket,message);

     if(message == "exit"){
        SendMessage(clientSocket,"user_exit");
        DeleteClient(clientSocket.GetSocketfd());
     }else{
        SendToAllUsers(message);
     }
}

bool EpollServerSocket::AddNewClient(Socket& clientSocket)
{
    if(Socket::Accept(clientSocket) == false){
        return false;
    }
    clientSocket.SetNonBlocking(true);

    if(epoll.Add(clientSocket.GetSocketfd(),EPOLLIN | EPOLLET) == false){
        return false;
    }

    return true;
}


void EpollServerSocket::DeleteClient(int sockfd)
{
    epoll.Delete(sockfd);

    delete clientSockets[sockfd];
    clientSockets.erase(sockfd);
}

void EpollServerSocket::SendToAllUsers(const std::string& message) const
{
    std::map<int,Socket*>::const_iterator iter;
    for(iter = clientSockets.begin();iter != clientSockets.end();iter++){
        SendMessage(*(iter->second),message);
    }
}


void EpollServerSocket::SendMessage(Socket& clientSocket,const std::string& message)const
{
    while(true){
        if(Socket::Send(clientSocket,message) == false){
            //this means the socket can be wrote
            if(errno == EINTR){
                return ;
            }
            //this means the cache queue is full,
            //sleep 1 second and send again
            if(errno == EAGAIN){
                sleep(1);
                continue;
            }
        }
        return ;
    }//end while
}

void EpollServerSocket::ReceiveMessage(Socket& clientSocket,std::string& message)
{
    bool done = true;

    while(done){
        int receiveNumber = Socket::Receive(clientSocket,message);
        if(receiveNumber == -1){
            //if errno == EAGAIN, that means we have read all data.
            if(errno != EAGAIN){
                std::cout << "ReceiveMessage error \n";
                DeleteClient(clientSocket.GetSocketfd()); 
            }

            return ;
            // End of file. The remote has closed the connection.
        }else if(receiveNumber == 0){
            DeleteClient(clientSocket.GetSocketfd());
        }
        //if receiveNumber is equal to MAXRECEIVE,
        //maybe there is data still in cache,so it has to read again
        if(receiveNumber == MAXRECEIVE){
            done = true;
        }else{
            done = false;
        }
    } 
}























