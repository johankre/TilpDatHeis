#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/stopp.h"
#include "driver/elevator_init.h"

#include "driver/lights.h"
#include "driver/elevDoor.h"

int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    init_elevator_position();

    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);
        
        if (floor > 0) {
            elevio_floorIndicator(floor); //setter indicator hver floor
        }

        

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
        
        if(elevio_stopButton()){
            stopButtonCaled();
        }

        stopLight();
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
