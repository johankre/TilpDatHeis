#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevio.h"
#include "con_load.h"
#include "queueLogic.h"


Queue init_queue(){
    Queue queue;
    queue.direction = QUEUE_UP;
    queue.next = 0;
    queue.last = 0;
    int num[2][4]= {{0, 0, 0, 0},
                    {0, 0, 0, 0}}
    queue.p_queue = &num;
    return queue;
}


void set_queue_last(Queue *queue, int num){
    queue->last = int num;
}


void clear_queue(Queue* queue){
    for(int i = 0; i < 8; i++){
        *(queue->p_queue + i) = 0;
    }
}


int sum_current_queue(Queue* queue){
    int sum = 0;
    for(int i = 0; i < 4; i++){
       sum = *(queue->p_queue + i + queue->direction * 4);
    }
    return sum;
}

void swith_queue_direction(Queue* queue){
    if(queue->direction == QUEUE_DOWN){
        queue->direction++;
    } else {
        queue->direction--;
    }
}


void set_queue_next(Queue *queue){

}
