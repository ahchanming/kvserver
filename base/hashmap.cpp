//
// Created by chanming on 16/6/9.
//

#include "hashmap.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define HashSize(n) (1 << n)
#define HashMask(n) (HashSize(n) - 1)
#define DEFAULT_SIZE_BIT 8

HashMap::HashMap() {
    m_ptHashTable = (hash_item**)calloc(HashSize(DEFAULT_SIZE_BIT), sizeof(void*));
    m_iSizeBit = DEFAULT_SIZE_BIT;
}

HashMap::HashMap(int sizeBit) {
    if (sizeBit < 20){
        m_ptHashTable = (hash_item**)calloc(HashSize(sizeBit), sizeof(void*));
        m_iSizeBit = sizeBit;
    }
}

void* HashMap::Get(char *key, int keyLength, unsigned long hashcode) {
    int hashRet = hashcode & HashMask(m_iSizeBit);

    m_ptLock->ReadLock();
    hash_item* tmp = m_ptHashTable[hashRet];
    while (tmp != NULL){
        if (memcmp(key, tmp->key, keyLength)){
            tmp = tmp->nextItem;
        }else{
            m_ptLock->Unlock();
            return tmp->content;
        }
    }
    m_ptLock->Unlock();
    return NULL;
}

int HashMap::Put(char *key, void* value, unsigned long hashcode) {
    printf("Ready 2 Put");
    int hashRet = hashcode & HashMask(m_iSizeBit);
    hash_item* ptItem = (hash_item*)malloc(sizeof(hash_item));
    ptItem->content = value;
    ptItem->key = key;

    m_ptLock->WriteLock();

    ptItem->nextItem = m_ptHashTable[hashRet];
    if (m_ptHashTable[hashRet] != NULL){
        m_ptHashTable[hashRet]->preItem = ptItem;
    }
    m_ptHashTable[hashRet] = ptItem;
    m_iTotal += 1;

    m_ptLock->Unlock();
}

bool itemCompare(void* value1, void* value2){
    return memcpy(value1, value2, sizeof(value1));
}
