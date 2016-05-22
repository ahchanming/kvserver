//
// Created by chanming on 16/5/7.
//

#include "thread.h"
#include "stdio.h"

Thread::Thread() {

}

Thread::~Thread() {

}

void Thread::Run() {
}

void* Thread::Run0(void *arg) {
    //printf("Hello World");
    //printf("The thread %u", (unsigned long)(arg));
    Thread* ptr = (Thread*)(arg);
    ptr->Run();
}

int Thread::Start() {
    return pthread_create(&pthread, NULL, Run0, this);
}
