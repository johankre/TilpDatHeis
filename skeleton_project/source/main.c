#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/stopp.h"
#include "driver/elevator_init.h"


int main(){
    // Setter opp queue struct
    Queue queue;
    Queue* p_queue = &queue;
    init_queue(p_queue);

    elevio_init();
   
    // Kontrolert oppstart
    init_elevator_position();

    dimAll();

    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        

        if(elevio_stopButton()){
            stopButtonCaled();
            clear_queue(p_queue);
        }

        
        

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
