//
// Created by chanming on 16/5/10.
//

#include <string.h>
#include <stdio.h>
#include "kv_cache.h"
const int g_iBlockCnt = 5;
const int g_iBlockSize = 64 * 8;  //64B
KVCache:: KVCache()
{
    m_pHead = new LRUNode();
    if(m_pHead == NULL)
    {
        //ERROR("new LRUNode error");
        return;
    }
    m_pTail = m_pHead;
    //DEBUG("m_pHead, m_pTail new suc");

    LRUNode *pTmp = NULL;
    for(int i = 1; i < g_iBlockCnt; i++)
    {
        pTmp = new LRUNode();
        if(pTmp == NULL)
        {
            //ERROR("new LRUNode error");
            return;
        }
        pTmp->pre = m_pTail;
        m_pTail->next = pTmp;
        m_pTail = pTmp;
    }
    m_pTail->next = m_pHead;
    m_pHead->pre = m_pTail;

    m_pTail = m_pHead; //已用的节点=0
    m_iUsedBlockCnt = 0;
}

KVCache:: ~KVCache()
{
    LRUNode *pTmp = NULL;
    int cnt = 0;

    m_pHead->pre->next = NULL;
    while(m_pHead != NULL)
    {
        pTmp = m_pHead;
        m_pHead = m_pHead->next;
        delete pTmp, pTmp = NULL;
        cnt++;
    }
    m_pTail = NULL;
    m_pHead = NULL;
    printf("delete cnt %d\n", cnt);
}

/**
 * 1.判断是否可存
 * 2.修改尾节点对应的索引节点
 * 3.修改尾节点的存储内容
 * 4.维护LRU链
 */
int KVCache:: Set(LRUNode *&pAddr, char * pValue, int iLen)
{
    //1
    if( iLen > g_iBlockSize)
    {
        //ERROR("add value size > BLOCKSIZE");
        return 1;
    }

    if(m_iUsedBlockCnt < g_iBlockCnt)
    {
        m_iUsedBlockCnt += 1;
    }
    else
    {
        m_pTail = m_pTail->pre;
        //TODO:删除索引节点的内存
    }
    //3
    strncpy(m_pTail->pValueAddr, pValue, iLen);
    pAddr = m_pTail;
    m_pTail = m_pTail->next;

    //4
    HealLRU(pAddr);
    //DEBUG("get out suc");
    return 0;
}

/**
 * 1.取值
 * 2.维护LRU链
 */
int KVCache::Get(LRUNode *pAddr, char *pValue, int &iLen)
{
    //DEBUG("get into");
    iLen = strlen(pAddr->pValueAddr);
    strncpy(pValue, pAddr->pValueAddr, iLen);
    printf("value : %s\n", pAddr->pValueAddr);
    //HealLRU(pAddr);
    //DEBUG("get out suc");
    return 0;
}


void KVCache:: HealLRU(LRUNode* pAddr)
{
    if(pAddr == m_pHead) return;
    pAddr->pre->next = pAddr->next;
    pAddr->next->pre = pAddr->pre;

    pAddr->next = m_pHead;
    m_pHead->pre = pAddr;

    m_pHead = pAddr;
    return;
}

void KVCache:: Output()
{
    printf("--st---\n");
    LRUNode* pCurrent = m_pHead;
    while(pCurrent != NULL)
    {
        printf("%s\n", pCurrent->pValueAddr);
        pCurrent = pCurrent->next;
        if(pCurrent == m_pHead) break;
    }
    printf("--ed---\n");
    return;
}