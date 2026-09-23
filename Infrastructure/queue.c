//
// Created by shadowleaves on 2026/9/23.
//

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int Elemtype;

typedef struct Queue {
    Elemtype data[MAXSIZE];
    int front;
    int rear;
    int element_number;
} Queue;

Queue* initQueue(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    queue->element_number = 0;
    return queue;
}

void push(Queue* queue, Elemtype e){
    if (queue->element_number < MAXSIZE){
        queue->data[queue->rear] = e;
        queue->element_number += 1;
        if (queue->front == MAXSIZE-1){
            queue->rear = 0;
            return;
        }else{
            queue->rear += 1;
            return;
        }
    }else{
        printf("The queue is already full!");
        return;
    }

}

Elemtype pop(Queue* queue){
    if (queue->element_number == 0){
        printf("The queu is empty!");
        return 0;
    }
    if (queue->front == MAXSIZE-1){
        Elemtype temp = queue->data[queue->front];
        queue->front = 0;
        queue->element_number -= 1;
        return temp;
    }else{
        Elemtype temp = queue->data[queue->front];
        queue->front += 1;
        queue->element_number -= 1;
        return temp;
    }
}
