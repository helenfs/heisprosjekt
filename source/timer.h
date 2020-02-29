#include <time.h>
#include "hardware.h"

/**
 * @brief Timer to start and stop the waiting time
 * */


/**
 * @brief Starts the timer
 * @param void No input argument(s)
 * */
void set_timer();


/**
 * @brief Checks if the timer have counted x seconds from the start time
 * @param void No input argument(s)
 * @return 1 haven't counted x seconds and 0 if the timer have counted x seconds
 * */
int check_timer();
