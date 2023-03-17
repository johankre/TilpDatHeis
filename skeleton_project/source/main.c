#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/stopp.h"
#include "driver/elevator_init.h"
#include "driver/queueLogic.h"

#include "lights.h"
#include "elevDoor.h"

int main(){
    // Setter opp queue struct
    Queue queue = {
        {{0,0,0,0}, {0,0,0,0}},
        -2,
        1,
        QUEUE_DOWN
    };
    Queue* p_queue = &queue;

    elevio_init();
   
    // Kontrolert oppstart
    init_elevator_position();

    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);


        // Oppdaterer queue last og queue next
        update_queue_internal(p_queue);
   
        openDoor();

        // Ser etter input
        input_floor(p_queue);
        drive_motor(p_queue);

        print_system(p_queue);

        // Utfører nødstopp
        if(elevio_stopButton()){
            stopButtonCaled();
            clear_queue(p_queue);
        }
        

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
