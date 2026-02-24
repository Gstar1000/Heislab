#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include <stdbool.h>



static double now_s(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

// --------------------
// Tilstander
// --------------------
typedef enum {
    ST_IDLE,
    ST_MOVING,
    ST_DOOR_OPEN,
    ST_STOP_HELD
} State;

int main(void){
    elevio_init();

    orders_init();

    State state = ST_IDLE;
    MotorDirection dir = DIRN_STOP;

    int lastFloor = 0;            // sist kjente etasje (0..3)
    double door_deadline = 0.0;   // når døra skal lukkes

    // Sørg for at motor ikke kjører ved start
    elevio_motorDirection(DIRN_STOP);
    lights_set_door_open_lamp(false);
    lights_set_stop_lamp(false);

    while(1){

        // ---- Les sensorer
        int floor = elevio_floorSensor();
        if(floor != -1){
            lastFloor = floor;
            lights_set_floor_indicator(floor);
        }

        bool stopPressed = elevio_stopButton();
        bool obstructed  = elevio_obstruction();

        // ---- STOPP: høyest prioritet
        if(stopPressed){
            lights_set_stop_lamp(true);
            elevio_motorDirection(DIRN_STOP);
            orders_clear_all();

            // Hvis i etasje: hold døra åpen mens STOPP holdes
            if(floor != -1){
                lights_set_door_open_lamp(true);
                state = ST_STOP_HELD;
            } else {
                state = ST_STOP_HELD; // mellom etasjer: bare stå stille
            }

        } else if(state == ST_STOP_HELD){
            // STOPP sluppet:
            lights_set_stop_lamp(false);

            // Hvis vi står i en etasje når stop slippes:
            if(floor != -1){
                // Start 3 sek dør-timer (hold åpen)
                lights_set_door_open_lamp(true);
                door_deadline = now_s() + 3.0;
                state = ST_DOOR_OPEN;
            } else {
                // Mellom etasjer: gå til normal styring
                lights_set_door_open_lamp(false);
                state = ST_IDLE;
            }
        }

        // Hvis vi er i STOP_HELD, gjør ingenting annet i denne iterasjonen
        if(state == ST_STOP_HELD){
            continue;
        }

        // ---- Poll knapper og oppdater ordrelys (ignorer hvis døra er åpen? valgfritt)
        orders_poll_buttons(false);
        lights_set_order_lamps_from_orders();

        // ---- Dørtilstand: motor skal alltid stå stille
        if(state == ST_DOOR_OPEN){
            elevio_motorDirection(DIRN_STOP);

            // Obstruksjon: forleng døra mens hindring finnes
            if(obstructed){
                door_deadline = now_s() + 3.0;
            }

            // Når tiden er ute og ingen obstruksjon: lukk døra
            if(now_s() >= door_deadline && !obstructed){
                lights_set_door_open_lamp(false);

                // Etter lukking: velg om vi skal kjøre eller idle
                dir = orders_next_dir(lastFloor, DIRN_STOP);
                state = (dir == DIRN_STOP) ? ST_IDLE : ST_MOVING;
            }

            continue; // viktig: ikke kjør motorvalg nedenfor
        }

        // ---- Normal logikk (IDLE / MOVING)
        // Hvis vi er i en etasje og skal stoppe her:
        if(floor != -1 && orders_should_stop(floor, dir)){
            elevio_motorDirection(DIRN_STOP);
            orders_clear_at_floor(floor);
            lights_set_order_lamps_from_orders();

            // Åpne dør i 3 sek
            lights_set_door_open_lamp(true);
            door_deadline = now_s() + 3.0;
            state = ST_DOOR_OPEN;

            continue; // viktig: ikke overskriv motoren etter stopp
        }

        // Velg retning basert på siste kjente etasje
        MotorDirection next = orders_next_dir(lastFloor, dir);

        if(next == DIRN_STOP){
            elevio_motorDirection(DIRN_STOP);
            dir = DIRN_STOP;
            state = ST_IDLE;
        } else {
            elevio_motorDirection(next);
            dir = next;
            state = ST_MOVING;
        }
    }
}