/**
 * @file
 * @brief Checks the elevator's position and if it's any orders above or below the elevator's current floor
 * */
#include <stdlib.h>
#include <stdio.h>
#include "hardware.h"

#include "queue.h"





/**
 * @brief Checks the elevator's position in real time
 * @param void No input argument(s)
 * @return The number of the floor, and -1 if between floors
 * */
int floor_indicator(void);


/**
 * @brief Checks if there's any order(s) above the elevator's current floor
 * @param current_floor The elevator's position
 * @return The number of floor with order(s); -1 if no order(s)
 * */
int get_ordered_above(int current_floor);


/**
 * @brief Checks if there's any order(s) below the elevator's current floor
 * @param current_floor The elevator's position
 * @return The number of floor with order(s); 4 if no order(s)
 * */
int get_ordered_below(int current_floor);
