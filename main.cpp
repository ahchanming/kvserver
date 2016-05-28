#include <pthread.h>
#include <cstdio>
#include <iostream>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>
#include "threadpool/task.h"
#include "threadpool/thread.h"
#include "threadpool/threadpool.h"
#include "kv/kv.h"
#include "kv/kv_index.h"
#include "kv/kv_file.h"
#include "kv_cache.h"
#include "ztest/echo_server.h"
#include "kv_server.h"
#include "client/kv_client.h"


pthread_t ntid;

#define MYPORT  8887
#define QUEUE   20
#define BUFFER_SIZE 1024


struct test{
    char name[80];
    int number;
};

void printids(const char *s){
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s  %u %u\n", s, (unsigned long)tid, (unsigned long)pid);
}

void * thr_fn(void *arg){
    //printf("New Thread");
    printf("this is new Thread\n");
    printf("new arg location is %u", arg);
    struct test* tt = (struct test*)arg;
    printf("%s", tt->name);
    printids("New Thread");
    return ((void *) 0);
}

class MyTask : public Task{
public:
    void Run(){
        printf("This a my Task\n");
    }
};

pthread_mutex_t mutex_t = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_t = PTHREAD_COND_INITIALIZER;
bool flag = false;

void * fun_consumer(void *arg){
    pthread_mutex_lock(&mutex_t);
    int time = 0;
    while (flag == false){
        printf("consumer wait %d\n", ++time);
        pthread_cond_wait(&cond_t, &mutex_t);
    }
    printf("consumer do OK\n");
    pthread_mutex_unlock(&mutex_t);
}

void * fun_provider(void *arg){
    sleep(10);
    pthread_mutex_lock(&mutex_t);
    flag = true;
    printf("privider do OK\n");
    pthread_mutex_unlock(&mutex_t);
    pthread_cond_signal(&cond_t);
}

class MyThread : public Thread{
public:
    void Run(){
        printf("HaHa This is a sub Thread");
    }
};

class CMTask : public Task{
private:
    int number;
public:
    CMTask(int number){
        this->number = number;
    }
    void Run(){
        printf("Tid is %u, the task Number is %d\n", (unsigned long)pthread_self(), number);
    }
};


void threadPoolTest(){
    Threadpool* pt = new Threadpool(3);
    pt->Start();
    for (int i =0; i < 20; i += 3){
        Task* tmp = new CMTask(i);
        pt->AddTask(tmp);
    }
    sleep(10);
}

void testPut(KV* kvClient, char* key, char *value){
    kvClient->put(key, value);
}

void testGet(KV* kvClient, char* key){
    char* result = kvClient->get(key);
    printf("Main::Get Key is [%s], Value is [%s]\n", key, result);
}

void socketTest(){
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(MYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ///bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }

    ///listen，成功返回0，出错返回-1
    if(listen(server_sockfd,QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }

    ///客户端套接字
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    ///成功返回非负描述字，出错返回-1
    int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn<0)
    {
        perror("connect");
        exit(1);
    }

    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer),0);
        if(strcmp(buffer,"exit\n")==0)
            break;
        fputs(buffer, stdout);
        send(conn, buffer, len, 0);
    }
    close(conn);
    close(server_sockfd);
}

void ttest(char* str){
    if (str != NULL)
        printf("%d\n", strlen(str));
    assert(str);
}

void ClientStart(){
    puts("ClientStart");
    KVClient* kvClient = new KVClient();
    kvClient->Init();
    //TestGet
    char* value = kvClient->Get("key1");
    printf("Client Test Get, Data is[%s]", value);
}

void ServerStart(){
    printf("ServerStart\n");
    KVServer* kvServer = new KVServer();
    kvServer->Start();
}

int main(int argc, char ** argv){
    if (argc < 2){
        printf("Argc number must more than 3");
    }
    if (strcmp("client", argv[1]) == 0){
        ClientStart();
    }else if (strcmp("server", argv[1]) == 0){
        ServerStart();
    }
    //printf(strlen(NULL));
//    KVServer* kvServer = new KVServer();
//    kvServer->Start();
//    socketTest();
//    printf("Hello WOrld");
//    KV* kvClient =new KV();
//    testPut(kvClient, "key1", "value1");
//    testPut(kvClient, "This is a Key2", "I am Value2");
//    testGet(kvClient, "key1");
//    testGet(kvClient, "This is a Key2");
}
