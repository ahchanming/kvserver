//
// Created by chanming on 16/5/8.
//

#include "threadpool.h"

Threadpool::Threadpool(int total) {
    for (int i = 0; i < total; ++i){
        m_threadVector.push_back(new ThreadPoolWorkThread(this, i));
        //m_threadVector.push_back(new ThreadPoolWorkThread(i));
    }
}

int Threadpool::Start() {
    for (int i = 0; i < m_threadVector.size(); ++i){
        //printf("Thread %d is start\n", i);
        m_threadVector[i]->Start();
    }
    return 0;
}

Task* Threadpool::GetTask(){
    pthread_mutex_lock(&m_mutex_t);
    while (m_taskQueue.empty()){
        pthread_cond_wait(&m_cond_t, &m_mutex_t);
    }
    Task* result = m_taskQueue.front();
    m_taskQueue.pop();
    pthread_mutex_unlock(&m_mutex_t);
    return result;
}

int Threadpool::AddTask(Task *task) {
    pthread_mutex_lock(&m_mutex_t);
    m_taskQueue.push(task);
    if (m_taskQueue.size() == 1){
        pthread_cond_signal(&m_cond_t);
    }
    pthread_mutex_unlock(&m_mutex_t);
    return 0;
}