#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevio.h"
#include "con_load.h"
#include "elevator_init.h"


/*
+------------------------------------------------------------------------------+
| Oppstart                                                                     |
+----+----------------------------------------------------------------------+--+
| O1 | Sørger systemet for at heisen kommer i en definert tilstand?         |j |
+----+----------------------------------------------------------------------+--+
| O2 | Ignoreres bestillinger før heisen har kommet i en definert tilstand? |j |
+----+----------------------------------------------------------------------+--+
| O3 | Ingnoreres stoppknappen under initialisering?                        |j |
+----+----------------------------------------------------------------------+--+
*/


void init_elevator_position(){
    // Posisjon til heisen
    int floor = elevio_floorSensor();

    // Hvis heisen ikke er i etasje 1, kjør heis nedover
    while(floor != 0){
        elevio_motorDirection(DIRN_DOWN);
        floor = elevio_floorSensor();
    }

    // Stopp heis når den er i etasje1
    elevio_motorDirection(DIRN_STOP);
    elevio_floorIndicator(1);
}