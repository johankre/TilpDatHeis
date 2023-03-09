
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "elevio.h"


void openDoor() {
    elevio_doorOpenLamp(1);
    nanosleep(&(struct timespec){0, 3*1000*1000*1000}, NULL);
    while elevio_obstruction() == 1 { //ser etter obstruksjon
        nanosleep(&(struct timespec){0, 3*1000*1000*1000}, NULL);
    }
    elevio_doorOpenLamp(0); //holder døren åpen i 3sek og lukker etterpå
}

//legg til openDoor i relevante filer