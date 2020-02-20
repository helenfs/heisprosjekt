#include "queue.h"
#include <stdio.h>

int queue_matrix[4][3];



typedef struct floor_value
{
	int floor;
	int value;
};



Map<int, int> floor_value{			// Husk å spørre om map
	{1, 0},
	{2, 1},
	{3, 2},
	{4, 3}
};

/*void order_queue_matrix (){
	for (int i = 0; i < 4; ++i){
		queueVector[i] = 0;
		printf("%d", queueVector[i]);
	}
}
*/


void empty_matrix (){
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i){
		for (int j = 0; j < 3; ++j) {
			queue_matrix[i][j] = 0;	
			printf("%d ", queue_matrix[i][j]);
		}
		printf("\n");
	}
}

void order_queue_matrix(){
	if (hardware_read_order(floor, order_type)) {
		queue_matrix[floor][order_type] = 1;
	}
}

//int hardware_read_order(int floor, HardwareOrder order_type) 			
//void hardware_command_order_light(int floor, HardwareOrder order_type, int  on) 		returnerer bestilling (etasje, ordre, skru på lys). 

//void hardware_command_floor_indicator_on 	(int  floor) 	returnerer ingenting, etasjelys