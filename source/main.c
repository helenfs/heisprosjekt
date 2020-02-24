#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "queue.h"
#include "states.h"
#include "hardware.h"
#include "floor.h"





static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}



int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Heisen er ikke i definert tilstand\n");
        exit(1);
    }
    clear_all_order_lights();    
    signal(SIGINT, sigint_handler);


    states();


 
    return 0;
}
