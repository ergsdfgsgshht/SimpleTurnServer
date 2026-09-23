#include <stdio.h>
#include "Components/NetworkMainLoop.h"

int main(void) {
    setvbuf(stdout, NULL, _IOLBF, 0);
    printf("Launching server...\n");
    pthread_t recv_thread, send_thread;
    pthread_create(&recv_thread, NULL, recvloop, NULL);
    pthread_create(&send_thread, NULL, sendloop, NULL);
    struct timespec duration = {
        .tv_sec = 1,
        .tv_nsec = 0
    };
    while (1) {thrd_sleep(&duration,NULL);}

    return 0;
}
