//
// Created by shadowleaves on 2026/9/23.
//

#include "Stunloop.h"

void* stunloop(void* args) {
    bool is_running = true;
    printf("Stunloop is running\n");
    while (is_running) {
        packet received_pack = pop(recv_messages_stun);
        if (received_pack.type == 127) {
            continue;
        }
        packet send_pack;  //创建用于返回客户端的包

        send_pack.sockaddress = received_pack.sockaddress; //构造包的目标地址

        //构造包的data
        char* data = malloc(sizeof(struct sockaddr));
        *((struct sockaddr*)data) = received_pack.sockaddress;
        send_pack.data = data;

        //构造包的length
        send_pack.length = sizeof(struct sockaddr);

        //将构造好的包放到队列中
        if (push(send_messages, send_pack) == -1) {
            printf("Error: The queue is full!\n");
        }

    }
}