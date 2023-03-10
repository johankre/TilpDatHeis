

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "elevio.h"


void openDoor() {
    elevio_doorOpenLamp(1);
    nanosleep(&(struct timespec){3, 0}, NULL);
    while (elevio_obstruction() == 1) { //ser etter obstruksjon
        
    }
    elevio_doorOpenLamp(0); //holder døren åpen i 3sek og lukker etterpå
}

//legg til openDoor i relevante filer