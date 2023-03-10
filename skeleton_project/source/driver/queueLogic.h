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


Queue init_queue();


void set_queue_last(Queue*, int);
void set_queue_next(Queue*);
void clear_queue(Queue*);
void swith_queue_direction(Queue*);
int sum_current_queue(Queue*);
int get_queue_last();
int get_queue_next();