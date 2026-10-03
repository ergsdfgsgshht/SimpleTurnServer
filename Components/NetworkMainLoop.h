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

//全局消息队列,定义于NetworkMainLoop.c,由recvloop初始化
extern Queue* recv_messages_stun;
extern Queue* recv_messages_register;
extern Queue* recv_messages_post;
extern Queue* recv_messages_inform;
extern Queue* send_messages;
extern int mainsock;

//服务器启动参数,由main函数解析命令行后传入recvloop
typedef struct server_config {
    const char* ip;
    uint16_t port;
} server_config;

#endif //SIMPLETURNSERVER_NETWORKMAINLOOP_H
