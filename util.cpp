//
// Created by wx on 2/19/21.
//

#include "util.h"
#include <signal.h>
#include <cstring>
#include <vector>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

void handle_for_sigpipe(){
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_flags = 0;
    sa.sa_handler = SIG_IGN;
    assert(sigaction(SIGPIPE, &sa, NULL) != 0);
}

void setSocketNonBlocking(int fd){
    int flag = fcntl(fd, F_GETFL, 0);
    if(flag == -1) return -1;
    if(fcntl(fd, F_SETFL, flag | O_NONBLOCK) == -1) return -1;
    return 0;
}

ssize_t readn(int fd, void* buff, size_t n){
    size_t nleft = n;
    ssize_t nread = 0;
    ssize_t readSum = 0;
    char *ptr = (char*)buff;
    while(nleft > 0){
        if((nread = read(fd, ptr, nleft)) < 0){
            if(errno == EINTR){
                nread = 0;
            }
            else if(errno == EAGAIN){
                return nread;
            }
            else{
                return -1;
            }
        }
        else if(nread == 0)
            break;
        readSum += nread;
        nleft -= nread;
        ptr += nread;
    }
    return readSum;
}

ssize_t writen(int fd, void *buff, size_t n){
    size_t nleft = n;
    ssize_t nwritten = 0;
    ssize_t writeSum = 0;
    char *ptr = (char*)buff;
    while (nleft > 0)
    {
        if ((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0)
            {
                if (errno == EINTR || errno == EAGAIN)
                {
                    nwritten = 0;
                    continue;
                }
                else
                    return -1;
            }
        }
        writeSum += nwritten;
        nleft -= nwritten;
        ptr += nwritten;
    }
    return writeSum;
}