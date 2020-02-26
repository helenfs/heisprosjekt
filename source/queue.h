#include "hardware.h"
#include <stdlib.h>

int queue_matrix[4][3];

//void order_queue_matrix (int i, int j);


void empty_all_orders();

void add_order(int floor, HardwareOrder order);
void delete_order(int floor, HardwareOrder order);

int queue_order_above(int current_floor, HardwareMovement motor_direction);
int queue_order_below(int current_floor, HardwareMovement motor_direction);