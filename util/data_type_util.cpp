//
// Created by chanming on 16/5/10.
//

#include <stdlib.h>
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
        result[0] = '0' - opt;
        total = 1;
        strncpy(&result[0 + 1], ItoA(strlen(key), KEY_LENGTH), KEY_LENGTH);
        total += KEY_LENGTH;
        strncpy(&result[total], ItoA(strlen(value), VALUE_LENGTH), VALUE_LENGTH);
        total += VALUE_LENGTH;
        strncpy(&result[total], key, strlen(key));
        total += strlen(key);
        strncpy(&result[total], value, strlen(value));
        total += strlen(value);
        return result;
}

