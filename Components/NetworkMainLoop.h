//
// Created by shadowleaves on 2026/9/23.
//

#ifndef SIMPLETURNSERVER_NETWORKMAINLOOP_H
#define SIMPLETURNSERVER_NETWORKMAINLOOP_H

#include "../Infrastructure/udp.h"
#include "../Infrastructure/queue.h"
#include "../Infrastructure/packet.h"
#include <stdbool.h>
#include <pthread.h>
#include <threads.h>

void* recvloop(void* arg);
void* sendloop(void* arg);

#endif //SIMPLETURNSERVER_NETWORKMAINLOOP_H
