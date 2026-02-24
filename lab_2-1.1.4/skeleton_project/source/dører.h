#ifndef DOOR_H
#define DOOR_H

#include <stdbool.h>

typedef enum {
    DOOR_CLOSED,
    DOOR_OPEN
} DoorState;

typedef struct {
    DoorState state;
    double t0;
    double open_time_s;
} Door;

void door_init(Door* d);

bool door_update(Door* d,
                 bool open_request,
                 bool at_floor,
                 bool stop_pressed,
                 bool obstruction,
                 double now);

#endif