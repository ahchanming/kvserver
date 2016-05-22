//
// Created by chanming on 16/5/14.
//

#include <stdio.h>
#include "logger.h"

Logger::Logger() {

}

void Logger::Debug(char* msg) {
    printf("%s", msg);
}

void Logger::ERROR(char *msg) {
    printf("%s", msg);
}