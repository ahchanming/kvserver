//
// Created by chanming on 16/5/8.
//

#include "kv_index.h"
#include "kv_common.h"
#include <string>

KVIndex::KVIndex() {

}

void*KVIndex::Get(char *key) {
    return InnerGet(key);
}

void*KVIndex::InnerGet(char *key) {
    m_wrlock.ReadLock();
    std::string str(key);
    if (m_indexMap[str] == NULL){
        printf("Index Get[%s],  m_indexMap is NULL", key);
        m_wrlock.Unlock();
        return NULL;
    }
    void* result = m_indexMap[str];
    m_wrlock.Unlock();
    return result;
}

int KVIndex::Update(char *key, void *value) {
    return InnerUpdate(key, value);
}

int KVIndex::InnerUpdate(char *key, void *value) {
    m_wrlock.WriteLock();
    m_indexMap[std::string(key)] = value;
    m_wrlock.Unlock();
    return 0;
}

int KVIndex::Put(char *key, void *value) {
    return Innerput(key, value);
}

int KVIndex::Innerput(char *key, void *value) {
    m_wrlock.WriteLock();
    m_indexMap[std::string(key)] = value;
    m_wrlock.Unlock();
    printf("KVIndex::KvIndex size is [%d]", m_indexMap.size());
    return 0;
}

int KVIndex::Del(char *key) {
    return InnerDel(key);
}

int KVIndex::InnerDel(char *key) {
    m_wrlock.WriteLock();
    m_indexMap[key] = NULL;
    m_wrlock.Unlock();
    return 0;
}
