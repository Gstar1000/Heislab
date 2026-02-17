#include "lys.h"

void floorupdate(int current_floor){
    if(elevio_floorSensor() != -1){
        current_floor = elevio_floorSensor();
    }
}

void setlights(MotorDirection dirn, int floor){
    while (1){elevio_floorIndicator(floor);}
    
    if(dirn == -1){
    }
    if(dirn == 1){
    }
    if(dirn == 0 && elevio_floorSensor() != -1){
        elevio_doorOpenLamp(1);
    }
    return;
}