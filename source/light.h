/**
 * @brief Sets the light in the elevator system
 */

#include <time.h>
#include "hardware.h"

#include "timer.h"
#include "queue.h"
#include "floor.h"

/**
 * @brief Program for obstruction signal
 * @param void No input argument(s)
 * */
int door_active(void);

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


/**
 * @brief Clear all the order lights
 */
void clear_all_order_lights();