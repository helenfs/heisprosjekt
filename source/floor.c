#include "floor.h"



void floor_indicator(void){
    for (int i = 0; i<HARDWARE_NUMBER_OF_FLOORS;i++){
        hardware_command_floor_indicator_on(i);
    }
}




//TRENGER: FUNKSJON SOM SAMMENLIGNER CURRENT_FLOOR MED RAD I MATRISE OG MOTORRETNING