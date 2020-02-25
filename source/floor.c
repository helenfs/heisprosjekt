#include "floor.h"



int floor_indicator(){
    for (int i = 0; i<HARDWARE_NUMBER_OF_FLOORS;i++){
        if (hardware_read_floor_sensor(i)) {
            hardware_command_floor_indicator_on(i);
            return i;
        }
    }
    return -1;
}

int get_ordered_floor(int current_floor, HardwareMovement motor_direction){
    for(int i=current_floor;i<HARDWARE_NUMBER_OF_FLOORS;i++){
        if(queue_matrix[i][motor_direction]){
            printf("%d ordered etasje: \n",i);
            return i;
        }
    }
    return -1;
}


//TRENGER: FUNKSJON SOM SAMMENLIGNER CURRENT_FLOOR MED RAD I MATRISE OG MOTORRETNING