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
    queue->next = -2;
    queue->last = 0;
    int num[2][4]= {{0, 0, 0, 0},
                    {0, 0, 0, 0}};
    queue->p_queue = &num;

}


void delete_queue_element(Queue* queue, int floor){
    *(queue->p_queue)[queue->direction][floor] = 0;
}


void set_queue_last(Queue *queue, int num){
    if(num > -1){
        queue->last = num;
    }
}


void clear_queue(Queue* queue){
    for(int q = 0; q < 2; q++){
        for(int floor = 0; floor < N_FLOORS; floor++){
            *(queue->p_queue)[q][floor] = 0;
        }
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
    int next_floor = -2;
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
    }


    // Finner nye ønsket etasje
    queue->next = set_queue_next(queue);
    if(queue->next == -2){
        swith_queue_direction(queue);
        queue->next = set_queue_next(queue);
    }

}


void input_floor(Queue* queue){
    for(int floor = 0; floor < N_FLOORS; floor++){
        for(int button = 0; button < N_BUTTONS; button++){

            // Sjekker om knappen er blit trykket
            if(elevio_callButton(floor, button)){

                // Plasser i opp-kø eller ned-kø
                if( button > 2){
                    *(queue->p_queue)[button][floor] = 1;
                }

                // Hvis cab-button blir trykt
                else {
                    // Plasser i opp-kø
                    if(floor > queue->last){
                        *(queue->p_queue)[0][floor] = 1;
                    }

                    // Plasser i ned-kø
                    else if(floor < queue->last){
                        *(queue->p_queue)[1][floor] = 1;
                    }

                    // Plassere i kø, i forhold til om heisen er i opp-kø eller ned-kø
                    else {
                        *(queue->p_queue)[queue->direction][floor] = 1;
                        }
                    }
                }
            }
        }
    }



void pirnt_queue(Queue* queue){
    for(int i = 0; i < 2; i++){
        for(int k = 0; k < 4; k++){
            printf(*(queue->p_queue)[i][k]);
            printf(" ");
        }
        printf("\n");
    }
}