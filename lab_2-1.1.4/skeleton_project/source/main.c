#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include <stdbool.h>
#include "dører.h"



/*int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    while(startup()!=true){}

    // while(1){
    //     int floor = elevio_floorSensor();

    //     if(floor == 0){
    //         elevio_motorDirection(DIRN_UP);
    //     }

    //     if(floor == N_FLOORS-1){
    //         elevio_motorDirection(DIRN_DOWN);
    //     }


    //     for(int f = 0; f < N_FLOORS; f++){
    //         for(int b = 0; b < N_BUTTONS; b++){
    //             int btnPressed = elevio_callButton(f, b);
    //             elevio_buttonLamp(f, b, btnPressed);
    //         }
    //     }

    //     if(elevio_obstruction()){
    //         elevio_stopLamp(1);
    //     } else {
    //         elevio_stopLamp(0);
    //     }
        
    //     if(elevio_stopButton()){
    //         elevio_motorDirection(DIRN_STOP);
    //         break;
    //     }
        
    //     nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    // }

    return 0;
}
*/




double get_time_seconds(){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec/1e9;
}

int main() {

    elevio_init();

    Door door;
    door_init(&door);   // eller bare 3.0 hvis du hardkodet

    while(1) {

        double now = get_time_seconds();

        bool at_floor = (elevio_floorSensor() != -1);
        bool stop_pressed = elevio_stopButton();
        bool obstruction = elevio_obstruction();

        // TEST: åpne døra hvis vi står i etasje og trykker cab-knapp i etg 0
        bool open_request = false;

        if(at_floor && elevio_callButton(0, BUTTON_CAB)){
            open_request = true;
        }

        bool door_is_open = door_update(&door,
                                        open_request,
                                        at_floor,
                                        stop_pressed,
                                        obstruction,
                                        now);

        if(door_is_open){
            elevio_motorDirection(DIRN_STOP);
        }
    }
}
