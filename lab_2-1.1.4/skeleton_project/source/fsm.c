#include "fsm.h"
#include "driver/elevio.h"

void heis_init(Heis* h, double now){
    h->state = HEIS_INIT;
    h->dir = DIRN_STOP;
    h->last_known_floor = -1;

    door_init(&h->door);


    elevio_motorDirection(DIRN_STOP);

    (void)now;
}

void heis_step(Heis* h, double now){
    
}