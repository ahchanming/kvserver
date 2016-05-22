//
// Created by chanming on 16/5/22.
//

#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "mysocket.h"

MySocket::MySocket() {

}

MySocket::MySocket(int _port) {
    m_socketId = socket(AF_INET,SOCK_STREAM, 0);
    m_sockAddr.sin_family = AF_INET;
    m_sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_sockAddr.sin_port = htons(_port);
    m_port = _port;
}

int MySocket::Bind() {
    return bind(m_socketId, (struct sockaddr*)&m_sockAddr, sizeof(m_sockAddr));
}

int MySocket::Listen() {
    return listen(m_socketId, 10);
}

MySocket* MySocket::Accept() {
    socklen_t len = sizeof(c_sockAddr);
    MySocket* tmpSocket = new MySocket();
    printf("Ready to Accept socketId is [%d], port is [%d]\n", m_socketId, m_port);
    int clientId = accept(m_socketId, (struct sockaddr*)&c_sockAddr, &len);
    //int clientId = accept(m_socketId, (struct sockaddr*)&c_sockAddr, &len);
    printf("Accept Ok, clientId is [%d]\n", clientId);
    if (clientId < 0){
        return nullptr;
    }
    tmpSocket->SetSocketId(clientId);
    return tmpSocket;
}

void MySocket::SetSocketId(int _socketId) {
    m_socketId = _socketId;
}

int MySocket::GetSocketId() {
    return m_socketId;
}

char* MySocket::Read() {
    char* ret = (char*)malloc(sizeof(char) * 256);
    memset(ret, 0, sizeof(ret));
    recv(m_socketId, ret, 256, 0);
    return ret;
}

int MySocket::Write(char *data, int len) {
    return send(m_socketId, data, len, 0);
}

void MySocket::Close() {
    close(m_socketId);
}






