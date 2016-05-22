//
// Created by chanming on 16/5/13.
//

#ifndef UNTITLED_KV_COMMON_H
#define UNTITLED_KV_COMMON_H

struct KVDO{
    char* key;
    char* value;
    int offset;
    int length;
};

struct IndexElement{
    char* key;
    int offset;
    int length;
};
#endif //UNTITLED_KV_COMMON_H
