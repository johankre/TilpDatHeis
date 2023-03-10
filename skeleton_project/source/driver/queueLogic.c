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
#include "elevDoor.h"


void init_queue(Queue* queue){
    queue->direction = QUEUE_UP;
    queue->next = 0;
    queue->last = 0;
    int num[2][4]= {{0, 0, 0, 0},
                    {0, 0, 0, 0}};
    queue->p_queue = &num;

}


void delete_queue_element(Queue* queue, int floor){
    *(queue->p_queue + floor + 4 * queue->direction) = 0;
}


void set_queue_last(Queue *queue, int num){
    if(num > -1){
        queue->last = num;
    }
}


void clear_queue(Queue* queue){
    for(int i = 0; i < 8; i++){
        *(queue->p_queue + i) = 0;
    }
}


int sum_current_queue(Queue* queue){
    int sum = 0;
    for(int i = queue->last; i < 4; i++){
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


int set_queue_next(Queue *queue){
    int next_floor = 0;
    if(queue->direction == QUEUE_UP)
        for(int i = queue->last; i < 4; i++){
            next_floor = *(queue->p_queue + i + queue->direction * 4);
            if(next_floor == 1){
                return i;
            }
    } else {
        for(int i = queue->last; i > -1; i--){
            next_floor = *(queue->p_queue + i + queue->direction * 4);
            if(next_floor == 1){
                return i;
            }
        }
    }
    return next_floor;
}


void update_queue_internal(Queue* queue){
    // Plasserer akktuel etasje i queue
    int floor = elevio_floorSensor();
    set_queue_last(queue, floor);

    // Ser om akktuel etasje er lik ønsket etasje
    if(queue->last == queue->next){
        delete_queue_element(queue, queue->next);
        openDoor();
    }


    // Finner nye ønsket etasje
    queue->next = set_queue_next(queue);
    if(queue->next == 0){
        swith_queue_direction(queue);
        queue->next = set_queue_next(queue);
    }

}


void input_floor(Queue* queue){
    for(int floor = 0; floor < N_FLOORS; floor++){
        for(int button = 0; button < N_BUTTONS; button++){
            printf("placeholder");
        }
    }
}