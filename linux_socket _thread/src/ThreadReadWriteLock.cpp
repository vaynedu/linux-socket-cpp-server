#include "ThreadReadWriteLock.h"

#include <iostream>


ThreadReadWriteLock::ThreadReadWriteLock()
{
    pthread_rwlock_init(&readWriteLock,NULL);
}
ThreadReadWriteLock::~ThreadReadWriteLock()
{
    pthread_rwlock_destroy(&readWriteLock);
}

bool ThreadReadWriteLock::SetReadLock()
{
    int retval;
    retval = pthread_rwlock_rdlock(&readWriteLock);
    if(retval != 0){
        std::cout<<"pthread_rwlock_rdlock failed\n";
        return false;
    }
    return true;
}


bool ThreadReadWriteLock::SetWriteLock()
{
    int retval;
    retval = pthread_rwlock_wrlock(&readWriteLock);
    if(retval != 0){
        std::cout<<"pthread_rwlock_wrlock\n";
        return false;
    }
    return true;
}

void ThreadReadWriteLock::UnLock()
{
   pthread_rwlock_unlock(&readWriteLock);
}



































