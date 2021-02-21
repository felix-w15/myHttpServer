//
// Created by wx on 2/19/21.
//

#include "Epoll.h"

int Epoll::epoll_init(int maxevents, int listen_num) {
    epoll_fd = epoll_create(listen_num + 1);
    if(epoll_fd == -1)
        return -1;
    events = new epoll_event[maxevents];
    return 0;
}