//
// Created by wx on 2/19/21.
//

#ifndef MYHTTPSERVER_UTIL_H
#define MYHTTPSERVER_UTIL_H

#include <cstdlib>


void handle_for_sigpipe();
int setSocketNonBlocking(int fd);


#endif //MYHTTPSERVER_UTIL_H
