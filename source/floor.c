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

int get_ordered_above(int current_floor){
    for(int i=current_floor;i<HARDWARE_NUMBER_OF_FLOORS;i++){
        for(int j = 0; j < 3; ++j){
            if(queue_matrix[i][j]){
            return i;
            }
        }
        
    }
    return -1;
}

int get_ordered_below(int current_floor){
    for(int i=current_floor;i>=0;i--){
        for(int j = 0; j < 3; ++j){
            if(queue_matrix[i][j]){
            return i;
            }
        } 
    }
    return 4;
}