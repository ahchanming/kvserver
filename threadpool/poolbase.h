//
// Created by chanming on 16/5/8.
//

#ifndef UNTITLED_BASEPOOL_H
#define UNTITLED_BASEPOOL_H

#include <stdio.h>
#include "task.h"

class PoolBase{
public:
    virtual Task* GetTask(){

    }
    virtual int AddTask(Task* task){

    }
    void prints(){
        printf("This is poolBase, ths location is %u\n", (unsigned long)(this));
    }
};
#endif //UNTITLED_BASEPOOL_H
