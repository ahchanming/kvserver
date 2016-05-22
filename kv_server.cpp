//
// Created by chanming on 16/5/22.
//

#include "kv_server.h"
#include "threadpool/threadpool.h"

KVServer::KVServer() {
    m_ptSocket = new MySocket(8000);
    m_ptThreadpool = new Threadpool(3);
}

int KVServer::Start() {
    if (m_ptSocket->Bind() < 0){
        return -1;
    }
    if (m_ptSocket->Listen() < 0){
        return -1;
    }
    if (m_ptThreadpool->Start() < 0){
        return -1;
    }
    while (1){
        MySocket* tmpSocket = m_ptSocket->Accept();
        Task* tmp = new TestTask(tmpSocket);
        m_ptThreadpool->AddTask(tmp);
    }
}



