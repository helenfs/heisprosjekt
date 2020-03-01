/**
 * @file
 * @brief The elevator's queue system
 */

#include "hardware.h"
#include <stdlib.h>
#include <stdio.h>




/**
 * @brief The queue system's matrix with floors and order types inlcuded
 * @param queue_matrix The queue system's matrix
 */
int queue_matrix[4][3];


/**
 * @brief Empty all the order(s) from the queue matrix
 * @param void No input argument(s)
 */ 
void empty_all_orders(void);


/**
 * @brief Add order to the queue matrix
 * @param floor Inquired floor
 * @param order Type of order
 */
void add_order(int floor, HardwareOrder order);


/**
 * @brief Deletes order from the queue matrix
 * @param floor Inquired floor
 * @param order Type of order
 */
void delete_order(int floor, HardwareOrder order);


/**
 * @brief Checks if there's any order above the elevator's current floor
 * @param current_floor The elevator's current floor
 * @param motor_direction The elevator's motor direction
 * @return 1 if it's a order; 0 otherwise
 */
int queue_order_above(int current_floor, HardwareMovement motor_direction);


/**
 * @brief Checks if there's any order below the elevator's current floor
 * @param current_floor The elevator's current floor
 * @param motor_direction The elevator's motor direction
 * @return 1 if it's a order; 0 otherwise
 */
int queue_order_below(int current_floor, HardwareMovement motor_direction);