//
// Created by chanming on 16/5/7.
//

#ifndef UNTITLED_THREAD_H
#define UNTITLED_THREAD_H


#include "task.h"
#include "pthread.h"

class Thread {
private:
    pthread_t pthread;
    static void* Run0(void* arg);
public:
    Thread();
    ~Thread();
    virtual void Run();
    int Start();
};


#endif //UNTITLED_THREAD_H
