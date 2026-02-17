#include "startup.h"
#include <stdbool.h>
bool startup(void){
    int floor = elevio_floorSensor();

    if(floor != -1){
        elevio_motorDirection(DIRN_STOP);
        return true; // ferdig
    }

    elevio_motorDirection(DIRN_DOWN);
    return false; // ikke ferdig enda
}



