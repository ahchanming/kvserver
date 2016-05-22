//
// Created by chanming on 16/5/10.
//

#ifndef UNTITLED_KV_CACHE_H
#define UNTITLED_KV_CACHE_H

#include <stdlib.h>

struct LRUNode
{
    LRUNode *pre, *next;
    char* pValueAddr; //对应的内存池地址
    char* pIndexAddr; //对应索引节点的地址
    LRUNode(): pre(NULL), next(NULL)
    {
        pValueAddr = (char *)malloc(64 * sizeof(char));
    }
};

class KVCache {
    public:

        KVCache();
        ~KVCache();

        int Set(LRUNode *&pAddr, char *pValue, int iLen);
        int Get(LRUNode *pAddr, char *pValue, int &iLen);

        void HealLRU(LRUNode* pAddr);
        void Output();

        LRUNode *m_pHead;
        LRUNode *m_pTail;
        int m_iUsedBlockCnt;
};


#endif //UNTITLED_KV_CACHE_H
