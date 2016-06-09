cmake_minimum_required(VERSION 3.3)
project(untitled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp threadpool/task.cpp threadpool/task.h threadpool/thread.cpp threadpool/thread.h threadpool/threadpool.cpp threadpool/threadpool.h threadpool/poolbase.h kv/kv.cpp kv/kv.h  kv/kv_index.cpp kv/kv_index.h kv/wrlock.h kv/kv_file.cpp kv/kv_file.h kv_cache.cpp kv_cache.h base/configure.cpp base/configure.h kv/kv_configure.cpp kv/kv_configure.h util/data_type_util.cpp util/data_type_util.h kv/kv_defind.h kv/kv_common.h  base/logger.cpp base/logger.h base/mysocket.cpp base/mysocket.h ztest/echo_server.cpp ztest/echo_server.h client/kv_client.cpp client/kv_client.h kv_server.cpp kv_server.h
        base/hashmap.h base/hashmap.cpp base/wrlock.h)
add_executable(untitled ${SOURCE_FILES})