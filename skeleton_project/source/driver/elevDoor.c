#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "elevio.h"

void openDoor() {
    elevio_doorOpenLamp(1);
    
    while (elevio_obstruction() == 1) { //ser etter obstruksjon
        
    }
    nanosleep(&(struct timespec){3, 0}, NULL);
    elevio_doorOpenLamp(0); //holder døren åpen i 3sek og lukker etterpå
}

//legg til openDoor i relevante filer