
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


void delete_queue_element(Queue* queue, int floor){
    queue->q_array[queue->direction][floor] = 0;
}


void set_queue_last(Queue *queue, int num){
    if(num > -1){
        queue->last = num;
    }
}


void clear_queue(Queue* queue){
    for(int q = 0; q < 2; q++){
        for(int floor = 0; floor < N_FLOORS; floor++){
            queue->q_array[q][floor] = 0;
        }
    }
}


int sum_current_queue(Queue* queue){
    int sum = 0;
    for(int i = queue->last; i < 4; i++){
        sum += queue->q_array[queue->direction][i];
    }
    return sum;
}


void swith_queue_direction(Queue* queue){
    if(queue->direction == QUEUE_DOWN){
        queue->direction--;
    } else {
        queue->direction++;
    }
}


int set_queue_next(Queue *queue){
    int next_floor = -2;
    if(queue->direction == QUEUE_UP)
        for(int i = queue->last; i < 4; i++){
            if(queue->q_array[QUEUE_UP][i] == 1){
                return i;
            }
            else {
                for(int i = 0; i < 4; i++){
                    if(queue->q_array[QUEUE_UP][i] == 1){
                        return i;
                    }
                }
            }
    } else {
        for(int i = queue->last; i > -1; i--){
            if(queue->q_array[QUEUE_DOWN][i] == 1){
                return i;
            }
            else {
                for(int i = 3; i > -1; i--){
                    if(queue->q_array[QUEUE_DOWN][i] == 1){
                        return i;
                    }
                }
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
                printf("%d ", floor);
                printf("%d ", button);

                // Plasser i opp-kø eller ned-kø
                if( button < 2){
                    queue->q_array[button][floor] = 1;
                }

                // Hvis cab-button blir trykt
                else {
                    // Plasser i opp-kø
                    if(floor > queue->last){
                        queue->q_array[QUEUE_UP][floor] = 1;
                    }

                    // Plasser i ned-kø
                    else if(floor < queue->last){
                        queue->q_array[QUEUE_DOWN][floor] = 1;
                    }

                    // Plassere i kø, i forhold til om heisen er i opp-kø eller ned-kø
                    else {
                        queue->q_array[queue->direction][floor] = 1;
                        }
                    }
                }
            }
        }
    }



void print_system(Queue* queue){

    printf("last: %d \n", queue->last);
    printf("next: %d \n", queue->next);
    printf("direction: %d \n", queue->direction);

    printf("Queue\n");
    for(int i = 0; i < 2; i++){
        for(int k = 0; k < 4; k++){
            printf("%d ", queue->q_array[i][k]);
        }
        printf("\n");
    } 
    printf("------------------------------------\n");
}

void drive_motor(Queue* queue){
    if(queue->last < queue->next){
        elevio_motorDirection(DIRN_UP);
    } else if(queue->next == -2){
        elevio_motorDirection(DIRN_STOP);
    } else {
        elevio_motorDirection(DIRN_DOWN);
    }
}