//
// Created by wx on 2/19/21.
//

#include "util.h"
#include <signal.h>
#include <cstring>
#include <vector>
#include <assert.h>

void handle_for_sigpipe(){
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_flags = 0;
    sa.sa_handler = SIG_IGN;
    assert(sigaction(SIGPIPE, &sa, NULL) != 0);
}