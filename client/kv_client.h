//
// Created by chanming on 16/5/22.
//

#ifndef UNTITLED_KV_CLIENT_H
#define UNTITLED_KV_CLIENT_H


#include "../base/mysocket.h"

class KVClient {
private:
    const int OPT_LENGTH = 1;
    const int KEY_LENGTH = 4;
    const int VALUE_LENGTH = 8;
    int inner_send(char* messageSend, int length);
    char* inner_get();
    int init_socket();
    int m_iServerSocket;
    MySocket* m_ptMySocket;
public:
    KVClient();
    char* Get(char* key);
    int Put(char* key, char* value);
    int Update(char* key, char* value);
    int Del(char* key);
    void Test();
    void Init();
};


#endif //UNTITLED_KV_CLIENT_H
