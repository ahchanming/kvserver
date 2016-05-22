//
// Created by chanming on 16/5/22.
//

#ifndef UNTITLED_MYSOCKET_H
#define UNTITLED_MYSOCKET_H


#include <netinet/in.h>

class MySocket {
private:
    int m_port;
    int m_socketId;
    struct sockaddr_in m_sockAddr, c_sockAddr;
public:
    MySocket();
    MySocket(int _port);
    int Bind();
    int Listen();
    MySocket* Accept();
    void SetSocketId(int _socketId);
    int GetSocketId();
    char* Read();
    int Write(char* data, int len);
    void Close();
};


#endif //UNTITLED_MYSOCKET_H
