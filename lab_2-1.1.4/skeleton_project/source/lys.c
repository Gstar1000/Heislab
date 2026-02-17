#include "lys.h"

void floorupdate(int current_floor){
    if(elevio_floorSensor() != -1){
        current_floor = elevio_floorSensor();
    }
}

void setlights(MotorDirection dirn, int floor, int ordersinside[], int ordersoutside[]){
    elevio_floorIndicator(floor);
    int targetfloor;
    ButtonType btn;
    for (int i = 0; i<=5; i++){
        if(i == 0){targetfloor = 1;}
        if(i == 1 || i == 2){targetfloor = 2;}
        if(i == 3 || i == 4){targetfloor = 3;}
        if(i == 5){targetfloor = 5;}
        
        if(i == 0 || i == 2 || i == 4){btn = BUTTON_HALL_UP;}
        if(i == 1 || i == 3 || i == 5){btn = BUTTON_HALL_DOWN;}
        elevio_buttonLamp(targetfloor, btn, ordersoutside[i]);
    }
    for(int i = 0; i<=3; i++){
        elevio_buttonLamp(i+1, BUTTON_CAB, ordersinside[i]);
    }

    if(dirn == 0 && elevio_floorSensor() != -1){
        elevio_doorOpenLamp(1);
    }
    return;
}