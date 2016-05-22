//
// Created by chanming on 16/5/22.
//

#include <stdio.h>
#include <string.h>
#include "echo_server.h"

EchoServer::EchoServer() {
    m_ptSocket = new MySocket(8787);
}

int EchoServer::Run() {
    int ret = m_ptSocket->Bind();
    printf("EchoServer::Bind Result[%d]\n", ret);
    ret = m_ptSocket->Listen();
    printf("EchoServer::Listen Result[%d]\n", ret);

    MySocket* tmpSocket = m_ptSocket->Accept();
    while (1){
        char* data = tmpSocket->Read();
        printf("Read From Client [%s]\n", data);
        tmpSocket->Write(data, strlen(data));
    }
}