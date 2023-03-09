#pragma once


typedef enum { 
    QUEUE_DOWN   = 0,
    QUEUE_UP     = 1
} QueueDirection;


typedef struct{
    int* p_queue[2][4];
    int next;
    int last;
}Queue; 


int* init_queue();


void set_queue_last(int);
void set_queue_next();
int get_queue_last();
int get_queue_next();