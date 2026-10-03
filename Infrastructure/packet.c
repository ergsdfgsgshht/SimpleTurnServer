//
// Created by shadowleaves on 2026/9/23.
//

#include "packet.h"

uint16_t getlength(char* buffer) {
    uint16_t temp = 0;
    memcpy(&temp,buffer+1,2);
    uint16_t length = ntohl(temp);
    return length;
}


