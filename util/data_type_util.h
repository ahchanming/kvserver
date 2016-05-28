//
// Created by chanming on 16/5/10.
//

#ifndef UNTITLED_DATA_TYPE_UTIL_H
#define UNTITLED_DATA_TYPE_UTIL_H


#include <string.h>

class DataTypeUtils {
public:
    static int Atoi(char *number);
    static char* ItoA(int number, int length);
    static char* DataEncode(int opt, char* key, char* value, int &length);
};


#endif //UNTITLED_DATA_TYPE_UTIL_H
