//
// Created by chanming on 16/5/8.
//

#ifndef UNTITLED_KV_INDEX_H
#define UNTITLED_KV_INDEX_H


#include "wrlock.h"
#include <map>
#include <cstring>

struct IndexStruct{
    int fileId;
    int offset;
    int length;
};

class KVIndex {
private:
    WRLock m_wrlock;
    int Innerput(char *key, void *value);
    void*InnerGet(char *key);
    int InnerUpdate(char *key, void *value);
    int InnerDel(char *key);
    std::map<std::string, void*> m_indexMap;
public:
    /**
     * 插入
     */
    int Put(char *key, void *value);
    /**
     * 获取
     */
    void*Get(char *key);
    /**
     * 更新
     */
    int Update(char *key, void *value);
    /**
     * 删除
     */
    int Del(char *key);

    KVIndex();
};


#endif //UNTITLED_KV_INDEX_H
