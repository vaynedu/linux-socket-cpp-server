#include "Epoll.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

Epoll::Epoll():fdNumber(0)
{
    rt.rlim_max= rt.rlim_cur = MAXEPOLLSIZE; 
    if(::setrlimit(RLIMIT_NOFILE,&rt) == -1){
        std::cout << "setlimit failed\n";
        exit(1);
    }
    epollfd = epoll_create(MAXEPOLLSIZE);
}

bool Epoll::Add(int fd,int eventsOption)
{
     event.data.fd = fd;
     event.events = eventsOption; //EPOLLIN | EPOLLET
     if(epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event) < 0){
         return false;
     }

     fdNumber++;
     return true;
}

bool Epoll::Delete(const int eventIndex)
{
    if(epoll_ctl(epollfd,EPOLL_CTL_DEL,events[eventIndex].data.fd,&event) < 0){
        return false;
    }
    fdNumber--;
    return true;
}

int Epoll::Wait()
{
    int eventNumber;
    eventNumber = epoll_wait(epollfd,events,fdNumber,-1);
    if(eventNumber < 0){
        std::cout << "epoll_wait  failed \n";
        exit(1);
    }
    return eventNumber;
}


int Epoll::GetEventOccurfd(const int eventIndex) const
{
    return events[eventIndex].data.fd;
}

int Epoll::GetEvents(const int eventIndex) const
{
    return events[eventIndex].events;
}



















