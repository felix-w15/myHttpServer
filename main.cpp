//
// Created by wx on 2/19/21.
//

#include "util.h"
#include "Epoll.h"
#include "ThreadPool.h"
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

static const int MAX_EVENTS = 5000;
static const int LISTENQ = 1024;
const int THEADPOOL_THREAD_NUM = 4;
const int QUEUE_SIZE = 65535;
const unsigned short PORT = 8888;

const std::string PATH = "/";

int socket_bind_listen(){
    int listen_fd = 0;
    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return -1;
    // 消除bind时"Address already in use"错误
    int optval = 1;
    if(setsockopt(listen_fd, SOL_SOCKET,  SO_REUSEADDR, &optval, sizeof(optval)) == -1)
        return -1;

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listen_fd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        return -1;

    if(listen(listen_fd, LISTENQ) == -1)
        return -1;

    if(listen_fd == -1){
        close(listen_fd);
        return -1;
    }

    return listen_fd;
}

int main(){
    handle_for_sigpipe();
    if(Epoll::epoll_init(MAX_EVENTS, LISTENQ) < 0){
        perror("epoll init error");
        return 1;
    }
    if(ThreadPool::threadpool_create(THEADPOOL_THREAD_NUM, QUEUE_SIZE) < 0){
        perror("Threadpool create failed");
        return 1;
    }
    int listen_fd = socket_bind_listen();
    if(listen_fd < 0){
        perror("socket bind failed");
        return 1;
    }
    if(setSocketNonBlocking(listen_fd) < =){
        perror("set socket non block failed");
        return 1;
    }

}