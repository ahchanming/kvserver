//
// Created by chanming on 16/5/8.
//

#ifndef UNTITLED_KV_H
#define UNTITLED_KV_H


#include "kv_file.h"
#include "../base/logger.h"
#include "kv_index.h"


class KV{
private:
    int InnerPut(char *key, char *value);
    char* InnerGet(char *key);
    int InnerUpdate(char *key, char *value);
    int InnerDel(char *key);
    char* Int2String(int number, int length);
    /**
     * 服务启动重新加载文件
     */
    int Load();
    /**
     * 存储文件
     */
    KVFile * m_ptFile;

    Logger* logger;

    KVIndex* m_ptIndex;

public:
    KV();
    ~KV();
    int put(char* key, char* value);
    char* get(char* key);
    int update(char* key, char* value);
    int del(char* key);
    char* DataFormat(bool del, char* key, char* value, int &total);
};


#endif //UNTITLED_KV_H
