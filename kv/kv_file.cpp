//
// Created by chanming on 16/5/8.
//

#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kv_file.h"
#include "../util/data_type_util.h"
#include "kv_defind.h"
#include "kv_common.h"

KVFile::KVFile(char *fileName) {
    m_fileId = open(fileName, O_CREAT | O_RDWR, 0666);

}

int KVFile::GetFileId() {
    return m_fileId;
}

KVFile::~KVFile() {
    close(m_fileId);
}

int KVFile::Write(char* data, int size) {
    return InnerWrite(data, size);
}

int KVFile::InnerWrite(char* data, int size) {
    int ret = lseek(m_fileId, 0, SEEK_END);
    if (ret == -1){
    }else{
        write(m_fileId, data, size);
        return ret;
    }
}


struct KVDO* KVFile::ReadOneData(int &offset) {
    int _offset = offset;
    lseek(m_fileId, offset, SEEK_SET);
    char* del = (char*)malloc(sizeof(char));
    int ret = read(m_fileId, del, 1);
    if (ret != 1){
        printf("%d -- %d\n", ret, 1);
        return NULL;
    }
    int isDel = DataTypeUtils::Atoi(del);
    offset += 1;

    char* keyLengthStr = (char*)malloc(sizeof(char) * KEY_LENGTH);
    ret = read(m_fileId, keyLengthStr, KEY_LENGTH);
    if (ret != KEY_LENGTH){
        printf("%d -- %d\n", ret, KEY_LENGTH);
        return NULL;
    }
    int keyLength = DataTypeUtils::Atoi(keyLengthStr);
    offset += KEY_LENGTH;

    char* valueLengthStr = (char*)malloc(sizeof(char) * VALUE_LENGTH);
    ret = read(m_fileId, valueLengthStr, VALUE_LENGTH);
    if (ret != VALUE_LENGTH){
        printf("%d -- %d\n", ret, VALUE_LENGTH);
        return NULL;
    }
    int valueLength = DataTypeUtils::Atoi(valueLengthStr);
    offset += VALUE_LENGTH;

    char* key = (char*)malloc(sizeof(char) * (keyLength + 1));
    key[keyLength] = 0;
    ret = read(m_fileId, key, keyLength);
    if (ret != keyLength){
        printf("%d -- %d\n", ret, keyLength);
        return NULL;
    }
    offset += keyLength;

    char* value = (char*)malloc(sizeof(char) * (valueLength + 1));
    value[valueLength] = 0;
    ret = read(m_fileId,value, valueLength);
    if (ret != valueLength){
        printf("%d -- %d\n", ret, valueLength);
        return NULL;
    }
    offset += valueLength;

    KVDO* result = new KVDO();
    result->key = key;
    result->value = value;
    result->offset = _offset;
    result->length = offset - _offset;
    printf("KeyLength is[%d], ValueLength is[%d]\n", keyLength, valueLength);
    printf("Key is [%s], Value is [%s]\n", key, value);
    return result;
}


