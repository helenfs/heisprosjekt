#include "queue.h"
#include <stdio.h>



typedef struct {
	int floor;
	int value;
}floor_value;



// Map<int, int> floor_value{			// Husk å spørre om map
// 	{1, 0},
// 	{2, 1},
// 	{3, 2},
// 	{4, 3}
// };

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



// void order_queue_matrix(int i, int j){

// 	for (i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i){
// 		for (j = 0; j < 3; ++j) {
// 			if (hardware_read_order(i, j)) {
// 				queue_matrix[i][j] = 1;	
// 			}
// 			//else {queue_matrix[i][j] = 0;}
// 			printf("%d ", queue_matrix[i][j]);

// 		}
// 		printf("\n");
// 	}
	
// }

void add_order(int i, HardwareOrder order){
	for (i=0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
		switch (order)
		{
		case HARDWARE_ORDER_UP:
			queue_matrix[i][HARDWARE_ORDER_UP]=1;
			break;
		case HARDWARE_ORDER_INSIDE:
			queue_matrix[i][HARDWARE_ORDER_INSIDE]=1;
			break;
		case HARDWARE_ORDER_DOWN:
			queue_matrix[i][HARDWARE_ORDER_DOWN]=1;
			break;
		default:
			break;
		}
	}
}

			//trenger funksjon add_order(queue_matrix) som returnerer den opdaterte queue_matrix

//int hardware_read_order(int floor, HardwareOrder order_type) 			
//void hardware_command_order_light(int floor, HardwareOrder order_type, int  on) 		returnerer bestilling (etasje, ordre, skru på lys). 

//void hardware_command_floor_indicator_on 	(int  floor) 	returnerer ingenting, etasjelys