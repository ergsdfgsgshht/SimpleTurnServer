#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Components/NetworkMainLoop.h"

int main(int argc, char* argv[]) {
    setvbuf(stdout, NULL, _IOLBF, 0);
    if (argc != 3) {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }
    char* end = NULL;
    long port = strtol(argv[2], &end, 10);
    if (*end != '\0' || port < 1 || port > 65535) {
        printf("Invalid port: %s\n", argv[2]);
        return 1;
    }
    server_config config = {
        .ip = argv[1],
        .port = (uint16_t)port
    };
    printf("Launching server...\n");
    pthread_t recv_thread, send_thread;
    pthread_create(&recv_thread, NULL, recvloop, &config);
    pthread_create(&send_thread, NULL, sendloop, NULL);
    struct timespec duration = {
        .tv_sec = 1,
        .tv_nsec = 0
    };
    while (1) {thrd_sleep(&duration,NULL);}

    return 0;
}
