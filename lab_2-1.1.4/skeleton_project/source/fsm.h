
#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include "orders.h"
#include "dører.h" 

typedef enum {
    HEIS_INIT = 0,
    HEIS_IDLE,
    HEIS_MOVING,
    HEIS_STOPPED
} State;

typedef struct {
    State state;
    MotorDirection dir;
    int last_known_floor; 
    Door door;
} Heis;

void heis_init(Heis* h, double now);
void heis_step(Heis* h, double now);

#endif