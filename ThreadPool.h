//
// Created by wx on 2/18/21.
//

#ifndef MYHTTPSERVER_THREADPOOL_H
#define MYHTTPSERVER_THREADPOOL_H

#include <functional>
#include <pthread.h>
#include <memory>
#include <vector>

const int MAX_THREADS = 1024;



typedef emum
{
    imiate_shutdown = 1,
    graceful_shutdown = 2
} threadpool_shutdown_t;

struct ThreadPoolTask{
    std::function<void(std::shared_ptr<void>)> fun;
    std::shared_ptr<void> args;
};

void myHandle(std::shared_ptr<void> req);
class ThreadPool{
private:
    static pthread_mutex_t lock;
    static pthread_cond_t notify;
    static std::vector<pthread_t> threads;
    static std::vector<ThreadPoolTask> queue;
    static int thread_count;
    static int head;
    static int tail;
    static int count;
    static int shutdown;
    static int started;
public:
    static int threadpoll_create(int _thread_count, int _queue_size);
    static int threadpool_add(std::shared_ptr<void> args, std::function<void(std::shared_ptr<void>)> = myHandle())
    static int threadpool_destory();
    static int threadpool_free();
    static void *threadpool_thread(void *args);
};

#endif //MYHTTPSERVER_THREADPOOL_H
