//
// Created by shadowleaves on 2026/9/23.
//

#include "queue.h"


Queue* initQueue(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    queue->element_number = 0;
    pthread_mutex_init(&queue->lock, NULL);
    return queue;
}

void push(Queue* queue, Elemtype e){
    pthread_mutex_lock(&queue->lock);
    if (queue->element_number < MAXSIZE){
        queue->data[queue->rear] = e;
        queue->element_number += 1;
        if (queue->front == MAXSIZE-1){
            queue->rear = 0;
            pthread_mutex_unlock(&queue->lock);
            return;
        }else{
            queue->rear += 1;
            pthread_mutex_unlock(&queue->lock);
            return;
        }
    }else{
        printf("The queue is already full!");
        pthread_mutex_unlock(&queue->lock);
        return;
    }

}

Elemtype pop(Queue* queue){
    pthread_mutex_lock(&queue->lock);
    if (queue->element_number == 0){
        printf("The queue is empty!");
        pthread_mutex_unlock(&queue->lock);
        return (Elemtype){0};
    }
    if (queue->front == MAXSIZE-1){
        Elemtype temp = queue->data[queue->front];
        queue->front = 0;
        queue->element_number -= 1;
        pthread_mutex_unlock(&queue->lock);
        return temp;
    }else{
        Elemtype temp = queue->data[queue->front];
        queue->front += 1;
        queue->element_number -= 1;
        pthread_mutex_unlock(&queue->lock);
        return temp;
    }
}
