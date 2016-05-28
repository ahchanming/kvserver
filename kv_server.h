//
// Created by chanming on 16/5/22.
//

#ifndef UNTITLED_KV_SERVER_H
#define UNTITLED_KV_SERVER_H


#include "base/mysocket.h"
#include "threadpool/threadpool.h"

class TestTask : public Task{
private:
    int m_iClientId;
    MySocket* m_ptSocket;

public:
    TestTask(MySocket* _socket){
        m_ptSocket = _socket;
    }

    void Run(){
        m_ptSocket->Write("HelloWorld", 10);
        while (1){
            char* data = m_ptSocket->Read();
            printf("Tid is %u, ClientId is [%d], ReadData is [%s]\n", (unsigned long)pthread_self(), m_ptSocket->GetSocketId(), data);
            if (data[0] == '.'){
                m_ptSocket->Close();
                break;
            }
            m_ptSocket->Write(data, strlen(data));
            sleep(60);
        }
        //printf("Tid is %u, the task Number is %d\n", (unsigned long)pthread_self(), m_iClientId);
    }
};


class KVServer {
private:
    MySocket* m_ptSocket;
    Threadpool* m_ptThreadpool;
    int m_iClientSet[20];
public:
    KVServer();
    int Start();
};


#endif //UNTITLED_KV_SERVER_H
