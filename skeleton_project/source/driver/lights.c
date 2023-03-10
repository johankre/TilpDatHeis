#pragma once



#include "elevio.h"


void dimAll() {
    for (int i = 1; i<5; ++i) {

    }
}

void stopLight() {
    if (elevio_stopButton) {
        elevio_stopLamp(1);
    }
    else {
        elevio_stopLamp(0);
        }
}