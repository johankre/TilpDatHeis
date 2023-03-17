#pragma once



#include "elevio.h"
#include "queueLogic.h"

void dimAll() {
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                
                    elevio_buttonLamp(f, b, 0); //lyset dimmes
                
            }
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

void dimLight(int floor) {
    if (floor in queue[0]) {
        elevio_buttonLamp(floor, BUTTON_HALL_DOWN, 0)
        elevio_buttonLamp(floor, BUTTON_CAB, 0)
        }
    else {
        elevio_buttonLamp(floor, BUTTON_HALL_UP, 0)
        elevio_buttonLamp(floor, BUTTON_CAB, 0)
    }
    
}