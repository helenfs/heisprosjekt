#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "queue.h"
//#include "states.h"
#include "hardware.h"

/*

static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}
*/
int p_queue[12];
int queue_matrix[4][3];

int main(){
    if(hardware_init()!=0) {            // Denne må være øverst!
        perror("Heisen er ikke i definert tilstand");
    }
    




    order_queue_matrix();
 


    /*for (int i = 0; i < 4*3; ++i){
		queueVector[i] = 0;
		printf("%d", queueVector[i]);
	}
    */
    return 0;
}
