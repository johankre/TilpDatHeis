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

extern struct Queue G_QUEUE;

void init_queue(Queue*);



void update_queue_internal(Queue*);
void set_queue_last(Queue*, int);
void delete_queue_element(Queue*, int);
void clear_queue(Queue*);
void swith_queue_direction(Queue*);
int set_queue_next(Queue*);
int sum_current_queue(Queue*);
int get_queue_last();
int get_queue_next();