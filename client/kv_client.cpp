//
// Created by chanming on 16/5/22.
//

#include <stdlib.h>
#include <tclDecls.h>
#include <string.h>
#include "kv_client.h"


KVClient::KVClient() {

}

char* KVClient::Get(char *key) {

}

int KVClient::Put(char *key, char *value) {

}

int KVClient::Update(char *key, char *value) {

}

int KVClient::Del(char *key) {

}

char* KVClient::Encode(int opt, char *key, char *value, int &len) {
    int keyLength = strlen(key);
    int valueLength = strlen(value);
    len = OPT_LENGTH + KEY_LENGTH + VALUE_LENGTH + keyLength + valueLength;
    char* result = (char*)malloc(sizeof(char) * len);
    result[0] = '0' - opt;

}

int KVClient::Decode(int &opt, char *key, char *value) {

}