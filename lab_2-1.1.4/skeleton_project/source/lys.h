#pragma once
#include <stdbool.h>
#include "driver/elevio.h"

// Bestillingslys (L1/L2) fra ordrelisten:
void lights_set_order_lamps_from_orders(void);

// Andre lys (om du vil samle dem her også):
void lights_set_floor_indicator(int floor);     // L3-L5
void lights_set_stop_lamp(bool on);             // L6
void lights_set_door_open_lamp(bool on);        // ofte brukt