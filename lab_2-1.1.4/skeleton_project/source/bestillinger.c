// Lage et set som tar inn bestillinger fra knapper
// Dersom noen skal opp, legges dere etasje i et set
// Dersom noen skal ned, legges deres etasje * -1 i samme set

// Sender heis til nærmeste etasje i retning heisen er på vei hvor det er lagt inn bestilling

// Skal finne neste etasje som skal hente opp folk

// Om utfører bestilling: må først gjøre ferdig bestillingen (dra opp eller ned én etasje), deretter gå til neste etasje
// Må sjekke om etasjen er den man skal til i bestillingen

#include "bestillinger.h"

void outside_addtoorders(int outsideorders[], int floor){
    outsideorders[floor-1] = 1;
}

void outside_ordercomplete(int outsideorders[], int floor){
    outsideorders[floor-1] = 0;
}

void inside_addtoorders(int insideorders[], int floor){
    
}

int getnextfloor(MotorDirection motordir, int currentfloor){
    if(motordir = 1){}
    for(int i = currentfloor-1 ; i<=5; i++) {
        if(orders[i] == 1){
            return i+1;
        }        
    }
}

