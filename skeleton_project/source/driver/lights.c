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

void buttonLight() {
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b); //btnpressed = 0 hvis ikke trykket, 1 hvis trykket
                if (btnPressed == 1) {
                    elevio_buttonLamp(f, b, btnPressed); //lyser hvis trykket, slukker hvis ikke 
                }
            }
        }
}

void dimLight(floor) {
    //if (floor in queue) {
        //for (int b = 0; b < N_Buttons; b++) {
            //elevio_buttonLamp(floor, b, 0)
        //}
    //}
}