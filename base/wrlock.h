//
// Created by chanming on 16/5/8.
//

#ifndef UNTITLED_WRLOCK_H
#define UNTITLED_WRLOCK_H

#include <pthread.h>
#include <stdio.h>

class WRLock {
private:
    pthread_rwlock_t q_lock;
    int status;
public:
    WRLock(){
        pthread_rwlock_init(&q_lock, NULL);
    }
    int ReadLock(){
        int ret = pthread_rwlock_rdlock(&q_lock);
        printf("WRLock::ReadLock, ret is [%d]\n", ret);
        return ret;
    }
    int WriteLock(){
        return pthread_rwlock_wrlock(&q_lock);
    }
    int Unlock(){
        int ret = pthread_rwlock_unlock(&q_lock);
        printf("WRLock::UnLock, ret is [%d]\n", ret);
        return ret;
    }
};


#endif //UNTITLED_WRLOCK_H
