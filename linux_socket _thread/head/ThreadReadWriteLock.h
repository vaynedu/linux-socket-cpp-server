#ifndef  THREADREADWRITELOCK_H
#define  THREADREADWRITELOCK_H

#include <pthread.h>

class ThreadReadWriteLock
{
     private:
        pthread_rwlock_t   readWriteLock;
     public:
        ThreadReadWriteLock();
        ~ThreadReadWriteLock();

        bool SetReadLock();
        bool SetWriteLock();
        void UnLock();

};


#endif
