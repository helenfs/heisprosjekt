#include "floor.h"



int floor_indicator(int i){
    for (i = 0; i<HARDWARE_NUMBER_OF_FLOORS;i++){
        if (hardware_read_floor_sensor(i)) {
            hardware_command_floor_indicator_on(i);
            return i;
        }
    }
    return 4;
}



//TRENGER: FUNKSJON SOM SAMMENLIGNER CURRENT_FLOOR MED RAD I MATRISE OG MOTORRETNING