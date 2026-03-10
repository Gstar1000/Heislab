#include "orders.h"

static bool orders[N_FLOORS][N_BUTTONS];

void orders_init(void) {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            orders[f][b] = false;
        }
    }
}

void orders_clear_all(void){
    for(int f = 0; f<N_FLOORS; f++){
        for(int b = 0; b<N_BUTTONS; b++){
            orders[f][b]=false;
        }
    }
}

void orders_add(int floor, ButtonType button){
    if(floor >= 0 && floor < N_FLOORS && button >= 0 && button < N_BUTTONS){
        orders[floor][button] = true;
    }
}

void orders_clear_at_floor(int floor){
    for(int b = 0; b < N_BUTTONS; b++){
        orders[floor][b] = false;
    }
}

bool orders_has_any(void){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(orders[f][b]){return true;}
        }
    }return false;
}

bool orders_has_at_floor(int floor){
    if (floor < 0 || floor >= N_FLOORS) {
        return false;
    }for(int b = 0; b < N_BUTTONS; b++){
        if(orders[floor][b]){
            return true;
        }
    }return false;
}

bool orders_has_above(int floor){
    if (floor < 0 || floor >= N_FLOORS) {
        return false;
    }for(int f = floor + 1; f < N_FLOORS; f++){
        if(orders_has_at_floor(f)){return true;}
    }return false;
}

bool orders_has_below(int floor){
    if (floor < 0 || floor >= N_FLOORS) {
        return false;
    }for(int f = floor - 1; f >= 0; f--){
        if(orders_has_at_floor(f)){return true;}
    }return false;
}

bool orders_should_stop(int floor, MotorDirection dir){
    if (floor < 0 || floor >= N_FLOORS) {
        return false;
    }if(orders[floor][BUTTON_CAB]){return true;}
    switch(dir){
        case DIRN_UP:
            if(orders[floor][BUTTON_HALL_UP]){return true;}
            if(orders[floor][BUTTON_HALL_DOWN] && !orders_has_above(floor)){return true;}
            return false;
        case DIRN_DOWN:
            if(orders[floor][BUTTON_HALL_DOWN]){return true;}
            if(orders[floor][BUTTON_HALL_UP] && !orders_has_below(floor)){return true;}
            return false;
        case DIRN_STOP:
            if(orders_has_at_floor(floor)){return true;}
            return false;
        default: 
            return false;
    }
}