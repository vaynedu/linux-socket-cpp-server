#ifndef   EPOLL_H
#define   EPOLL_H

#include "Socket.h"
#include <sys/epoll.h>
#include <sys/resource.h>



const int  MAXEPOLLSIZE = 10;

class Epoll
{
   public:
       Epoll();
       bool Add(int fd,int eventsOption);

       //Returns the number of triggered events
       int Wait();
       bool Delete(const int eventIndex);
       int  GetEventOccurfd(const int eventIndex) const;
       int  GetEvents(const int eventIndex) const;

   private:
        int epollfd;
        int fdNumber;
        struct epoll_event event;
        struct epoll_event events[MAXEPOLLSIZE];
        struct rlimit  rt;

};

#endif
