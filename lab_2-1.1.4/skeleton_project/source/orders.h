#ifndef ORDERS_H
#define ORDERS_H

#include <stdbool.h>
#include "driver/elevio.h"





void orders_init(void);
void orders_clear_all(void);

void orders_add(int floor, ButtonType button);
void orders_clear_at_floor(int floor);

bool orders_has_any(void);
bool orders_has_at_floor(int floor);
bool orders_has_above(int floor);
bool orders_has_below(int floor);

bool orders_should_stop(int floor, MotorDirection dir);

/*
    Valgfritt, men veldig nyttig for testing/debug og senere lys-modul:
    Returnerer true hvis det ligger en bestilling på (floor, button).
*/
bool orders_get(int floor, ButtonType button);

#endif