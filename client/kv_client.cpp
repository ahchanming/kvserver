//
// Created by chanming on 16/5/22.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include "kv_client.h"
#include "../util/data_type_util.h"
#include "../kv/kv_defind.h"


KVClient::KVClient() {

}

char* KVClient::Get(char *key) {
    int sendLength = 0;
    char* messageSend = DataTypeUtils::DataEncode(OPT_GET, key, NULL, sendLength);
    int sendResult = m_ptMySocket->Write(messageSend, sendLength);
    printf("Send Message is[%s], length is [%d], result is [%d]", messageSend, strlen(messageSend), sendResult);
    char* readresult = m_ptMySocket->Read();
    printf("Read Result is [%s]\n", readresult);
    return readresult;
}

int KVClient::Put(char *key, char *value) {

}

int KVClient::Update(char *key, char *value) {

}

int KVClient::Del(char *key) {

}

int KVClient::inner_send(char *messageSend, int length) {
    return 0;
}

char* KVClient::inner_get() {
    char* messageWrite = m_ptMySocket->Read();
    return messageWrite;
}

void KVClient::Test() {
    printf("HelloWorld\n");
}

void KVClient::Init() {
    if (init_socket() < 0){
        printf("init_socket Error\n");
        return;
    }
}

int KVClient::init_socket() {
    m_ptMySocket = new MySocket();
    m_ptMySocket->SetPort(8000);
    m_ptMySocket->SetIP("127.0.0.1");
    if (m_ptMySocket->Connect() < 0){
        printf("Connect Server Error");
        return -1;
    }
    char* buffer;
    buffer = m_ptMySocket->Read();
    printf("Recieve From Server: %s\n", buffer);
    return 0;
}
