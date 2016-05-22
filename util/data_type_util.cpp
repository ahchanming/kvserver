//
// Created by chanming on 16/5/10.
//

#include "data_type_util.h"

int DataTypeUtils::Atoi(char *number) {
        int result = 0;
        int len = strlen(number);
        for (int i = 0; i < len; ++i){
            result = result * 10 + number[i] - '0';
        }
        return result;
}