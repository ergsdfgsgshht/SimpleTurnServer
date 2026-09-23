//
// Created by shadowleaves on 2026/9/23.
//

#ifndef SIMPLETURNSERVER_PACKET_H
#define SIMPLETURNSERVER_PACKET_H

#include "udp.h"
enum PacketType: uint8_t {
    STUN,  //获取自己的公网地址
    REGISTER,  //注册账户
    POST,  //向服务器绑定账号目前的地址
    INFORM, //告知另一用户自己想要连接
};
typedef enum PacketType PacketType;

//暂存队列中的包体结构
struct packet {
    PacketType type; //应用层识别哪种枚举类型的包,以便分配给不同的线程处理
    struct sockaddr sockaddress;  //记录客户端地址,便于发送回去
    uint8_t length;  //记录数据长度
    char* data;    //指向应用层包文具体数据,处理线程接受到后应当及时释放
};
typedef struct packet packet;

uint8_t getlength();

#endif //SIMPLETURNSERVER_PACKET_H