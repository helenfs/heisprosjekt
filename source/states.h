/**
 * @file
 * @brief Final state machine (FSM) for the elevator.
 */

#include "hardware.h"
#include <stdio.h>
#include <time.h>

#include "queue.h"
#include "light.h"
#include "floor.h"
#include "timer.h"

#define motor_up 1
#define motor_down -1



/**
 * @brief Different state types used in @c states
 */
typedef enum {         
    START_UP, IDLE, EMERGENCY_STOP, DOOR_OPEN, MOVE_UP, MOVE_DOWN
} State;



/**
 * @brief Program for the different states the elevetor can be in
 * @param void No input argument(s)
 */
void states(void);




