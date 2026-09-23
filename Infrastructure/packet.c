//
// Created by shadowleaves on 2026/9/23.
//

#include "packet.h"

uint8_t getlength(char* buffer) {
    uint8_t length = 0;
    char* lenptr = (char*)&length;
    *lenptr = *(buffer+1);
    *(lenptr+1) = *(buffer+2);
    return length;
}
