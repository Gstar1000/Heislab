#include "startup.h"
#include <stdbool.h>
bool startup_status(void){
    int floor = elevio_floorSensor();
    return (floor >= 0 && floor <= 3);
}


