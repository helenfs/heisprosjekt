#include "queue.h"
#include <stdio.h>


void empty_all_orders (){
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i){
		for (int j = 0; j < 3; ++j) {
			queue_matrix[i][j] = 0;	
			printf("%d ", queue_matrix[i][j]);
		}
		printf("\n");
	}
}



void add_order(int floor, HardwareOrder order){
	//for (floor=0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
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
	//}
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
		if(queue_matrix[f][HARDWARE_MOVEMENT_UP]){
			
		}
	}
	return 0;
}



     //   if (hardware_read_floor_sensor(i)) {

			//trenger funksjon add_order(queue_matrix) som returnerer den opdaterte queue_matrix

//int hardware_read_order(int floor, HardwareOrder order_type) 			
//void hardware_command_order_light(int floor, HardwareOrder order_type, int  on) 		returnerer bestilling (etasje, ordre, skru på lys). 
