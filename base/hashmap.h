//
// Created by chanming on 16/6/9.
//

#ifndef UNTITLED_HASHMAP_H
#define UNTITLED_HASHMAP_H


#include "../kv/wrlock.h"

typedef  struct _hash_item{
    const char* key;
    void* content;
    struct _hash_item* preItem;
    struct _hash_item* nextItem;
}hash_item;

class HashMap {
private:
    hash_item** m_ptHashTable = 0;
    WRLock* m_ptLock = new WRLock();
    int m_iSizeBit;
    int m_iTotal = 0;
public:
    HashMap();
    HashMap(int sizeBit);
    void* Get(char* key, int keyLength, unsigned long hashcode);
    int Put(char* key, void* value, unsigned long hashcode);
};


#endif //UNTITLED_HASHMAP_H
