//
// Created by wx on 2/19/21.
//

#include "ThreadPool.h"
#include "requestData.h"
#include <pthread.h>

pthread_mutex_t ThreadPool::lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  ThreadPool::notify = PTHREAD_COND_INITIALIZER;
std::vector<pthread_t> ThreadPool::threads;
std::vector<ThreadPoolTask>ThreadPool::queue;
int ThreadPool::thread_count = 0;
int ThreadPool::queue_size = 0;
int ThreadPool::head = 0;
int ThreadPool::tail = 0;
int ThreadPool::count = 0;
int ThreadPool::shutdown = 0;
int ThreadPool::started = 0;

int ThreadPool::threadpool_create(int _thread_count, int _queue_size) {
    bool err = false;
    if(_thread_count <= 0 || _thread_count >= MAX_THREADS || _queue_size <= 0 || _queue_size > MAX_QUEUE){
        _thread_count = 4;
        _queue_size = 1024;
    }
    thread_count = 0;
    queue_size = _queue_size;
    head = tail = count = 0;
    shutdown = started = 0;

    threads.resize(_thread_count);
    queue.resize(_queue_size);

    for(int i = 0; i < _thread_count; i++){
        if(pthread_create(&(threads[i]), 0, threadpool_thread, (void*)(0)) != 0)
            return -1;
        started++;
        thread_count++;
    }
    if(err){
        return -1;
    }
    return 0;
}

void myHandler(std::shared_ptr<void> req)
{
    std::shared_ptr<requestData> request = std::static_pointer_cast<requestData>(req);
    request->handleRequest();
}


int ThreadPool::threadpool_add(std::shared_ptr<void> args, std::function<void(std::shared_ptr<void>)> fun){
    int next, err = 0;
    if(pthread_mutex_lock(&lock) != 0)
        return THREADPOOL_LOCK_FAILURE;
    do {
        if(count == queue_size){
            err = THREADPOOL_QUEUE_FULL;
            break;
        }
        if(shutdown){
            err = THREADPOOL_SHUTDOWN;
            break;
        }
        next = (tail + 1) % queue_size;
        queue[tail].fun = fun;
        queue[tail].args = args;
        tail = next;
        ++count;

        if(pthread_cond_signal(&notify) != 0){
            err = THREADPOOL_LOCK_FAILURE;
            break;
        }
    } while(false);

    if(pthread_mutex_unlock(&lock) != 0)
        err = THREADPOOL_LOCK_FAILURE;

    return err;

}

void *ThreadPool::threadpool_thread(void *args){
    while(true){
        ThreadPoolTask task;
        pthread_mutex_lock(&lock);
        while(count == 0 && !shutdown)
            pthread_cond_wait(&notify, &lock);
        if((shutdown == immediate_shutdown) ||
            (shutdown == graceful_shutdown && count == 0))
            break;
        task.fun = queue[head].fun;
        task.args = queue[head].args;
        queue[head].fun = NULL;
        queue[head].args.reset();
        head = (head + 1) % queue_size;
        --count;
        pthread_mutex_unlock(&lock);
        (task.fun)(task.args);
    }
    --started;

    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}