#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/stopp.h"
#include "driver/elevator_init.h"
#include "driver/queueLogic.h"


int main(){
    // Setter opp queue struct
    Queue queue;
    Queue* p_queue = &queue;
    init_queue(p_queue);

    elevio_init();
   
    // Kontrolert oppstart
    init_elevator_position();

    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);


        // Oppdaterer queue last og queue next
        update_queue_internal(p_queue);


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }


        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        

        // Utfører nødstopp
        if(elevio_stopButton()){
            stopButtonCaled();
            clear_queue(p_queue);
        }
        

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
