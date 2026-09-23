#include "udp.h"    // 自定义头文件用双引号,尖括号只在系统目录查找

int createUDPsocket(){
    int sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sock == -1){
        exit(1);  //异常处理
    }else{
        return sock;
    }
}

struct sockaddr* construct_server_address(const char* ip_str, uint16_t port){
    static struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));  // 清零,包括sin_zero
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(ip_str);
    serveraddr.sin_port = htons(port);           // 使用传入的port参数
    return (struct sockaddr*)&serveraddr;
}

ssize_t udpsend(int sock, const void* buf, size_t len, const struct sockaddr* serveraddr){
    ssize_t result = sendto(sock, buf, len, 0, serveraddr, sizeof(struct sockaddr_in));
    if (result == -1){
        perror("fail to sendto");
        return -1;
    }else{
        printf("Succeed! \n");
        return result;   // 返回实际发送的字节数,信息量比0大
    }
}