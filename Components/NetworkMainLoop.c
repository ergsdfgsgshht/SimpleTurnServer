//
// Created by shadowleaves on 2026/9/23.
//

#include "NetworkMainLoop.h"

//全局消息队列,由recvloop初始化,供各处理线程读写
Queue* recv_messages_stun = NULL;
Queue* recv_messages_register = NULL;
Queue* recv_messages_post = NULL;
Queue* recv_messages_inform = NULL;
Queue* send_messages = NULL;
int mainsock = 0;

void* recvloop(void* arg) {
    server_config* config = (server_config*)arg;
    recv_messages_stun = initQueue();
    recv_messages_register = initQueue();
    recv_messages_post = initQueue();
    recv_messages_inform = initQueue();
    send_messages = initQueue();

    mainsock = createUDPsocket();

    struct sockaddr* self = construct_server_address(config->ip, config->port);
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
    bool is_running = true;
    while (is_running) {

        packet temp = pop(send_messages);  //取出要发送的信息
        if (temp.type == 127) {
            continue;
        }

        char* message;
        struct sockaddr target_address;  //初始化构建udp包体需要填入的两个参数

        uint16_t total_length = temp.length+3;
        message = malloc(total_length);     //初始化网络包体应用层结构

        memcpy(message,&temp.type,1);  //填充包的首位:type

        uint16_t net_length = htons(temp.length);
        memcpy(message+1,&net_length,2);  //填充包的第1,2字节

        memcpy(message+3,temp.data,temp.length);  //填充包的data字段

        target_address = temp.sockaddress; //获取目标ip

        udpsend(mainsock,message,temp.length+3,&target_address); //发送数据

        free(temp.data);
        free(message);    //释放内存

    }
    return NULL;
}
