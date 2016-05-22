//
// Created by chanming on 16/5/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "kv_defind.h"
#include "kv_common.h"

KV::KV() {
    printf("This a Kv construct\n");
    m_ptFile = new KVFile("/Users/chanming/cpp/kvdata/kv_data.txt");
    //logger = new Logger();
    m_ptIndex = new KVIndex();
    Load();
}

KV::~KV() {
}

char* KV::get(char *key) {
    printf("This is a get method\n");
    return InnerGet(key);
}

int KV::put(char *key, char *value) {
    printf("This is a put method\n");
    return InnerPut(key, value);
}

int KV::update(char *key, char *value) {
    printf("This is a Update method\n");
}

int KV::del(char *key) {
    printf("This is a delete method\n");
}

int KV::InnerDel(char *key) {

}

char* KV::InnerGet(char *key) {
    IndexStruct* indexStruct = (IndexStruct*)(m_ptIndex->Get(key));
    if (indexStruct == NULL){
        printf("KV::Index Struct is NULL\n");
        return NULL;
    }else{
        printf("fid[%d], offset[%d], length[%d]\n", indexStruct->fileId, indexStruct->offset, indexStruct->length);
        int offset = indexStruct->offset;
        KVDO* kvDO = m_ptFile->ReadOneData(offset);
        //todo memery
        return kvDO->value;
    }
}

int KV::InnerPut(char *key, char *value) {
    int length = 0;
    char* inputData = DataFormat(1, key, value, length);
    IndexStruct* indexStruct = new IndexStruct();
    indexStruct->fileId = m_ptFile->GetFileId();
    indexStruct->length = strlen(inputData);
    int _offset = m_ptFile->Write(inputData, length);
    indexStruct->offset = _offset;
    m_ptIndex->Put(key, indexStruct);
}

int KV::InnerUpdate(char *key, char *value) {

}

char* KV::DataFormat(bool del, char *key, char *value, int &total) {
    char* result = (char*) malloc(sizeof(char) * (1 + KEY_LENGTH + VALUE_LENGTH) + sizeof(key) + sizeof(value));
    if (del){
        result[0] = '1';
    }else{
        result[0] = '0';
    }
    total = 1;
    strncpy(&result[0 + 1], Int2String(strlen(key), KEY_LENGTH), KEY_LENGTH);
    total += KEY_LENGTH;
    strncpy(&result[total], Int2String(strlen(value), VALUE_LENGTH), VALUE_LENGTH);
    total += VALUE_LENGTH;
    strncpy(&result[total], key, strlen(key));
    total += strlen(key);
    strncpy(&result[total], value, strlen(value));
    total += strlen(value);
    return result;
}

char* KV::Int2String(int number, int length) {
    char* result = (char*) malloc(sizeof(char) * length);
    for (int i = length; i > 0; --i){
        result[i - 1] = (char)('0' + number % 10);
        number /= 10;
    }
    return result;
}

int KV::Load() {
    printf("Here to Load\n");
    printf("FileId is %d\n", m_ptFile->GetFileId());
    if (m_ptFile->GetFileId() <= 0){
        //logger->ERROR("Error fileId <= 0");
        return -1;
    }
    int offset = 0;
    int total = 0;
    while (true){
        printf("To Load, Offset is %d\n", offset);
        KVDO* tmpKVDO = m_ptFile->ReadOneData(offset);
        if (tmpKVDO == NULL){
            //logger->Debug("File Read %d datas", total);
            printf("File Read %d Datas", total);
            break;
        }
        if (total > 5){
            break;
        }
        total ++;
        IndexStruct* indexStruct = new IndexStruct();
        indexStruct->fileId = m_ptFile->GetFileId();
        indexStruct->offset = tmpKVDO->offset;
        indexStruct->length = tmpKVDO->length;
        m_ptIndex->Put(tmpKVDO->key, indexStruct);
    }
    return -1;
}