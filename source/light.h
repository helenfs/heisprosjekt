/**
 * @brief Sets the light on the elevator system
 */

#include <time.h>
#include "hardware.h"

#include "timer.h"
#include "queue.h"
#include "floor.h"

/**
 * @brief Program for the door and obstruction signal
 * @param void No input argument(s)
 * */
int door_active(void);

/**
 * @brief Polls the order buttons
 * @param void No input argument(s)
 */
void poll_buttons(void);

/**
 * @brief Program for emergency stop button
 * @param void No input argument(s)
 */
void emergency_stop_active();


/**
 * @brief Clear all the order lights
 */
void clear_all_order_lights();