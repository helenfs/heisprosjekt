#include "queue.h"


void empty_all_orders (void){
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i){
		for (int j = 0; j < 3; ++j) {
			queue_matrix[i][j] = 0;	
		}
	}
}



void add_order(int floor, HardwareOrder order){
		switch (order)
		{
		case HARDWARE_ORDER_UP:
			queue_matrix[floor][HARDWARE_ORDER_UP]=1;
			break;
		case HARDWARE_ORDER_INSIDE:
			queue_matrix[floor][HARDWARE_ORDER_INSIDE]=1;
			break;
		case HARDWARE_ORDER_DOWN:
			queue_matrix[floor][HARDWARE_ORDER_DOWN]=1;
			break;
		default:
			break;
		}
}


void delete_order(int floor, HardwareOrder order_type){
	queue_matrix[floor][order_type]=0;
	hardware_command_order_light(floor,order_type,0);
}



int queue_order_above(int current_floor, HardwareMovement motor_direction){
	for(int f=current_floor; f< HARDWARE_NUMBER_OF_FLOORS; ++f){
		if(queue_matrix[f][motor_direction]){
			return 1;
		}
	}
	return 0;
}


int queue_order_below(int current_floor, HardwareMovement motor_direction){
	for(int f=current_floor; f>=0; --f){
		if(queue_matrix[f][motor_direction]){
			return 1;
		}
	}
	return 0;
}