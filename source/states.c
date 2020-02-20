#include <stdio.h>
#include "states.h"
#include <time.h>
#include "hardware.h"

void obstruction_or_emergencystop_active(void){
    time_t time=clock();

    while ((hardware_read_obstruction_signal() || hardware_read_stop_signal())!=0){
        hardware_command_door_open(1);

    }
    while (difftime(clock(),time) >=3.0){          
        
        
        for (int floor=0;floor<=HARDWARE_NUMBER_OF_FLOOR; i++){
            for (int j = 0; j < 3; ++j) {
             hardware_command_order_light(i, j, 1);                          //Når lys er på skal orderen leggges inn i kømatrisen, hvordan??
                if(hardware_read_order (i, j)){

                }
            }
        }
        
        
        hardware_read_order (floor, order_type);        //noe med for løkke     
        hardware_command_door_open(1);
    }
    //Går til tilstand IDLE
}

void states(void){
    State current_state;
    while(1){
        switch (current_state)
        {
        case START_UP:
            hardware_command_door_open(0);
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}      
            if (hardware_read_floor_sensor(0)){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            }
            break;
        case IDLE: 
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(0);
            hardware_read_floor_sensor(1);
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            break;
        case MOVE_UP:
            hardware_command_door_open(0);
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            //if(heisen ankommer bestillingsetasjen) {motor stopper; current_state=DOOR_OPEN}
            break;
        case MOVE_DOWN:
            hardware_command_door_open(0);
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            if(floor==ordered_floor && current_direction==ordered_direction) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP); 
                current_state=DOOR_OPEN;
                }
            break;
        case DOOR_OPEN:
            hardware_command_door_open(1);
            obstruction_or_emergencystop_active();
			current_state=IDLE;
			if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            break;
		case EMERGENCY_STOP:
            hardware_command_stop_light(1);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            //KØMATRISE SETTES TIL 0 = TØMMMES
            if (hardware_read_floor_sensor(1)){current_state=DOOR_OPEN;}
        	current_state=IDLE;
			break;
       
		default: 
			current_state=IDLE;	
        }
    }
}

/*
set_timer(3)
int timer_active = 1;
time_t timestamp = clock();
is_time_elapsed(void)
if(clock - timestamp > 0)
return 1
else
return 0
*/