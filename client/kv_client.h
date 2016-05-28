//
// Created by chanming on 16/5/22.
//

#ifndef UNTITLED_KV_CLIENT_H
#define UNTITLED_KV_CLIENT_H


class KVClient {
private:
    const int OPT_LENGTH = 1;
    const int KEY_LENGTH = 4;
    const int VALUE_LENGTH = 8;
public:
    KVClient();
    char* Get(char* key);
    int Put(char* key, char* value);
    int Update(char* key, char* value);
    int Del(char* key);
    char* Encode(int opt, char* key, char* value, int &len);
    int Decode(int &opt, char* key, char* value);
};


#endif //UNTITLED_KV_CLIENT_H
