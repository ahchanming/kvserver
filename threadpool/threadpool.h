//
// Created by chanming on 16/5/8.
//

#ifndef UNTITLED_THREADPOOL_H
#define UNTITLED_THREADPOOL_H

#include <queue>
#include <vector>
#include "thread.h"
#include "poolbase.h"

class ThreadPoolWorkThread : public Thread{
private:
    int number;
    PoolBase* m_ptrPool;
public:
    ThreadPoolWorkThread(PoolBase* ptr){
        this->m_ptrPool = ptr;
    }

    ThreadPoolWorkThread(int number){
        this->number = number;
    }

    ThreadPoolWorkThread(PoolBase* ptr, int number){
        this->m_ptrPool = ptr;
        this->number = number;
    }

    void Run(){
        m_ptrPool->prints();
        while (1) {
            Task *m_ptTask = m_ptrPool->GetTask();
            m_ptTask->Run();
        }
        //printf("This is a worker thread, the number is %d\n", number);
    }
};

class Threadpool : public PoolBase{
private:
    std::vector<ThreadPoolWorkThread*> m_threadVector;
    std::queue<Task*> m_taskQueue;
    pthread_mutex_t m_mutex_t = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t m_cond_t = PTHREAD_COND_INITIALIZER;
public:
    int AddTask(Task* task);
    Threadpool(int total);
    Task* GetTask();
    int Start();
};


#endif //UNTITLED_THREADPOOL_H
