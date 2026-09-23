//
// Created by shadowleaves on 2026/9/23.
//

#ifndef SIMPLETURNSERVER_QUEUE_H
#define SIMPLETURNSERVER_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "packet.h"

#define MAXSIZE 1024
typedef packet Elemtype;

typedef struct Queue {
    Elemtype data[MAXSIZE];
    int front;
    int rear;
    int element_number;
} Queue;

Queue* initQueue();

void push(Queue* queue, Elemtype e);

Elemtype pop(Queue* queue);

#endif //SIMPLETURNSERVER_QUEUE_H
