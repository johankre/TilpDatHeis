#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevio.h"
#include "con_load.h"
#include "queueLogic.h"



/*
+------------------------------------------------------------------------------------------------------+
| Sikkerhet                                                                                            |
+----+----------------------------------------------------------------------------------------------+--+
| S1 | Stopper heisen når stoppknappen trykkes?                                                     |j |
+----+----------------------------------------------------------------------------------------------+--+
| S2 | Blir bestillingene slettet (lysene på bestillingsknappene slukkes) når stoppknappen trykkes? |n |
+----+----------------------------------------------------------------------------------------------+--+
| S3 | Er lyset i stoppknappen tent mens stoppknappen er trykket?                                   |j |
+----+----------------------------------------------------------------------------------------------+--+
| S4 | Ignoreres trykk på alle bestillingsknappene mens stoppknappen er trykket?                    |j |
+----+----------------------------------------------------------------------------------------------+--+
| S5 | Blir heisen stående i ro etter at stoppknappen er sluppet?                                   |j |
+----+----------------------------------------------------------------------------------------------+--+
| S6 | Husker heisen hvor den er ved nødstopp mellom etasjer?                                       |n |
+----+----------------------------------------------------------------------------------------------+--+
| S7 | Åpnes dæren hvis stoppknappen aktiveres i en etasje?                                         |j |
+----+----------------------------------------------------------------------------------------------+--+
*/

void stopButtonCaled(Queue* queue){
    // Stopper motoren til heisen
    elevio_motorDirection(DIRN_STOP);

    // Skrur på stopplyset
    elevio_stopLamp(1);

    //Hvis heis er i etasje, åpne døra
    if(elevio_floorSensor() > -1){
        elevio_doorOpenLamp(1);
    }

    while(elevio_stopButton()){
        printf("elevator stopped\n");
    }

    // Clear queue
    clear_queue(queue);

    // Skrur av stoppLamp og dorrOpenLamp
    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);    
}