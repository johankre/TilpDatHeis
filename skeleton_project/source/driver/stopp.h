#pragma once


typedef enum { 
    QUEUE_DOWN   = 0,
    QUEUE_UP     = 1
} QueueDirection;


typedef struct{
    int *p_queue;
    int next;
    int last;
    QueueDirection direction;
}Queue; 


void stopButtonCaled(Queue* queue);
