//
// Created by shadowleaves on 2026/9/23.
//

#include "NetworkMainLoop.h"




void* recvloop(void* arg) {
    Queue* recv_messages_stun = initQueue();
    Queue* recv_messages_register = initQueue();
    Queue* recv_messages_post = initQueue();
    Queue* recv_messages_inform = initQueue();

    Queue* send_messages = initQueue();

    int mainsock = createUDPsocket();
    struct sockaddr* self = construct_server_address("103.207.68.106",5140);
    socklen_t addrlen = sizeof(struct sockaddr);
    if (bind(mainsock,self,sizeof(struct sockaddr)) == -1) {
        perror("Error:Cannot bind to self");
        exit(-1);
    }
    int* sharedsock = malloc(sizeof(int));
    *sharedsock = mainsock;
    bool is_running = true;
    printf("Receive loop started\n");
    while(is_running) {
        //创建buffer和地址结构体等待数据接收
        char buffer[1024];
        struct sockaddr received_address;
        size_t received = recvfrom(mainsock,buffer,sizeof(buffer),0,&received_address,&addrlen);
        //将网络数据包格式转化为队列中的单体pack结构
        packet pack;
        pack.data = NULL;
        pack.type = buffer[0];
        pack.sockaddress = received_address;
        pack.length = getlength(&buffer);
        if (pack.length != 0) {
            char* data = malloc(pack.length);
            for (int i = 0; i < pack.length; i++) {
                data[i] = buffer[3+i];
            }
            pack.data = data;
        }

        //将单体pack结构压入对应队列中
        if (pack.type == STUN) {
            push(recv_messages_stun,pack);
            printf("Received STUN request.\n");
        }else if (pack.type == REGISTER) {
            push(recv_messages_register,pack);
        }else if (pack.type == POST) {
            push(recv_messages_post,pack);
        }else if (pack.type == INFORM) {
            push(recv_messages_inform,pack);
        }else {
            printf("Unknown packet type.\n");
        }
    }
    return NULL;
}

void* sendloop(void* arg) {
    struct timespec duration = {
        .tv_sec = 1,
        .tv_nsec = 0
    };
    thrd_sleep(&duration,NULL);
    printf("Send loop started\n");
    return NULL;
}
