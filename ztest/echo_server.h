//
// Created by chanming on 16/5/22.
//

#ifndef UNTITLED_ECHO_SERVER_H
#define UNTITLED_ECHO_SERVER_H


#include "../base/mysocket.h"

class EchoServer {
private:
    MySocket* m_ptSocket;
    int m_port;
public:
    EchoServer();
    int Run();
};


#endif //UNTITLED_ECHO_SERVER_H
