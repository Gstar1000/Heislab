#include "dører.h"
#include "driver/elevio.h"

void door_init(Door* d) {
    d->state = DOOR_CLOSED;
    d->t0 = 0.0;
    d->open_time_s = 3.0;
    elevio_doorOpenLamp(0);
}

bool door_update(Door* d,
                 bool open_request,
                 bool at_floor,
                 bool stop_pressed,
                 bool obstruction,
                 double now)
{
    switch(d->state){
        case DOOR_CLOSED:
            if(open_request && at_floor){
                elevio_doorOpenLamp(1);
                d->state = DOOR_OPEN;
                d->t0 = now;
            }
            break;
        
        case DOOR_OPEN:
            if(elevio_stopButton || elevio_obstruction){
                d->t0 = now;
            }
            else if(now - d->t0 >= d->open_time_s){
                elevio_doorOpenLamp(0);
                d->state = DOOR_CLOSED;
            }
            break;
    }
    return (d->state == DOOR_OPEN);
}


