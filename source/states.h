/**
 * @file
 * @brief Program for the elevator door.
 *
 * 
 */
#include "hardware.h"
#include <stdio.h>
#include <time.h>
#include "queue.h"

/**
 * @brief State type used in @c states
 */
typedef enum {         //Nødvendig med typedef før enum?
    START_UP, IDLE, EMERGENCY_STOP, DOOR_OPEN, MOVE_UP, MOVE_DOWN
} State;


/**
 * @brief Program for obstruction or
 emergencystop active while the elevator is on a floor
 * @param void No input argument(s)
 */
void obstruction_or_emergencystop_active(void);


/**
 * @brief Program for the different states the elevetor can be in
 * @param void No input argument(s)
 */
void states(void);


/**
 * @brief Program for obstruction signal
 * @param void No input argument(s)
 * */
void obstruction_active(void);

/**
 * @brief Polls the order buttons
 * @param void No input argument(s)
 */
void poll_buttons(void);

/**
 * @brief PProgram for obstruction signal
 * @param void No input argument(s)
 */
void emergency_stop_active();

void clear_all_order_lights();