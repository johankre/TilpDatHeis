
#pragma once



#include "elevio.h"

void openDoor() {
    elevio_doorOpenLamp(1);
    nanosleep(&(struct timespec){0, 3*1000*1000*1000}, NULL);
    elevio_doorOpenLamp(0);
}

//legg til openDoor i relevante filer