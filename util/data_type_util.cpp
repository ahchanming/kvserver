//
// Created by chanming on 16/5/10.
//

#include <stdlib.h>
#include <stdio.h>
#include "data_type_util.h"
#include "../kv/kv_defind.h"

int DataTypeUtils::Atoi(char *number) {
    int result = 0;
    int len = strlen(number);
    for (int i = 0; i < len; ++i){
        result = result * 10 + number[i] - '0';
    }
    return result;
}


char* DataTypeUtils::ItoA(int number, int length) {
    char* result = (char*) malloc(sizeof(char) * length);
    for (int i = length; i > 0; --i){
            result[i - 1] = (char)('0' + number % 10);
            number /= 10;
    }
    return result;
}

char* DataTypeUtils::DataEncode(int opt, char *key, char *value, int &total) {
    char* result = (char*) malloc(sizeof(char) * (OPT_LENGTH + KEY_LENGTH + VALUE_LENGTH) + sizeof(key) + sizeof(value));
    result[0] = '0' + opt;
    total = 1;
    strncpy(&result[0 + 1], ItoA(strlen(key), KEY_LENGTH), KEY_LENGTH);
    total += KEY_LENGTH;

    if (value != NULL){
        strncpy(&result[total], ItoA(strlen(value), VALUE_LENGTH), VALUE_LENGTH);
    }else{
        strncpy(&result[total], ItoA(0, VALUE_LENGTH), VALUE_LENGTH);
    }
    total += VALUE_LENGTH;

    strncpy(&result[total], key, strlen(key));
    total += strlen(key);

    if (value != NULL){
        strncpy(&result[total], value, strlen(value));
        total += strlen(value);
    }
    return result;
}

int DataTypeUtils::DataDecode(int &opt, char* &key, char* &value,  const char *decodeStr) {
    if (strlen(decodeStr) < 9){
        printf("DecodeStr Lenth Error, decodeStr is [%s]\n", decodeStr);
        return -1;
    }
    opt = '0' + decodeStr[0];
    char* keyLength = (char *)malloc(sizeof(char) * 4);
    char* valueLength = (char*) malloc(sizeof(char) * 4);
    strncpy(keyLength, decodeStr + OPT_LENGTH, KEY_LENGTH);
    strncpy(valueLength, decodeStr + OPT_LENGTH + KEY_LENGTH, VALUE_LENGTH);
    int iKeyLength= Atoi(keyLength);
    int iValueLength = Atoi(valueLength);
    if (iKeyLength < 0){
        printf("keyLength invaild, data is[%s]\n", keyLength);
        return  -1;
    }else{
        char* tmpKey = (char*)malloc(sizeof(char) * iKeyLength + 1);
        strncpy(tmpKey, decodeStr + OPT_LENGTH + KEY_LENGTH + VALUE_LENGTH, iKeyLength);
        tmpKey[iKeyLength] = 0;
        key = tmpKey;
    }
    if (iValueLength < 0){
        printf("valueLength invaild, data is[%s]\n", valueLength);
        return -1;
    }else{
        char* tmpValue = (char*)malloc(sizeof(char) * iValueLength + 1);
        strncpy(tmpValue, decodeStr + OPT_LENGTH + KEY_LENGTH +VALUE_LENGTH + iKeyLength, iValueLength);
        tmpValue[iValueLength] = 0;
        value = tmpValue;
    }
    free(keyLength);
    free(valueLength);
}

