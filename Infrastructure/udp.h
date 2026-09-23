#pragma once

#include <stdio.h>
#include <stdint.h>     // uint16_t
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

//创建udp socket
int createUDPsocket();

//分别输入服务器的ip地址和端口,返回构造的地址结构体
struct sockaddr* construct_server_address(const char* ip_str, uint16_t port);

//输入sock,要发送的字符串(及其长度),以及服务器地址结构体
ssize_t udpsend(int sock, const void* buf, size_t len, const struct sockaddr* serveraddr);

