/**
 * @file
 * @brief Program for the elevator door.
 *
 * 
 */
#include "hardware.h"

/**
 * @brief State type used in @c states
 */
typedef enum {         //Nødvendig med typedef før enum?
    START_UP, IDLE, EMERGENCY_STOP, DOOR_OPEN, MOVE_UP, MOVE_DOWN
} State;


/**
 * @brief Program for obstruction or emergencystop active while the elevator is on a floor
 * @param void No input argument(s)
 */
void obstruction_or_emergencystop_active(void);


/**
 * @brief Program for the different states the elevetor can be in
 * @param void No input argument(s)
 */
void states(void);


