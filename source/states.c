#include "states.h"
#include <stdio.h>
#include <time.h>
#include "hardware.h"

// void obstruction_or_emergencystop_active(void){
//     time_t time=clock();
//     while (hardware_read_obstruction_signal() || hardware_read_stop_signal()){
//         hardware_command_door_open(1);
//         while (difftime(clock(),time) >=3.0){          
//             hardware_command_door_open(1);
//         }         
//     }
// }

void clear_all_order_lights(){
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

void emergency_stop_active(){
    //time_t time = clock();
    while(hardware_read_stop_signal()){
       // time = clock();
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        hardware_command_stop_light(1);
        printf("read stop signal\n");
    }
    // while (difftime(clock(),time) <= 3000000.0){          
    //     //hardware_command_stop_light(1);
    //     //printf("time digff\n");
    // }
}
    
void obstruction_active(void){
    time_t time=clock();
    while (hardware_read_obstruction_signal()){
        time =clock();
        hardware_command_door_open(1);
     }
    while (difftime(clock(),time) <= 3000000.0){
        hardware_command_door_open(1);
     }
 }     


 void poll_buttons(void){
    for (int i=0; i<HARDWARE_NUMBER_OF_FLOORS;i++){
        if (hardware_read_order(i, HARDWARE_ORDER_DOWN)){
            hardware_command_order_light(i,HARDWARE_ORDER_DOWN,1);
            add_order(i,HARDWARE_ORDER_DOWN); 	                    
        }   
        if (hardware_read_order(i, HARDWARE_ORDER_UP)){
            hardware_command_order_light(i,HARDWARE_ORDER_UP,1);
            add_order(i,HARDWARE_ORDER_UP); 	
        }
        if(hardware_read_order(i,HARDWARE_ORDER_INSIDE)){
            hardware_command_order_light(i,HARDWARE_ORDER_INSIDE,1);
            add_order(i,HARDWARE_ORDER_INSIDE);
        }
    }
 }
        
        
    //     hardware_read_order (i, order_type);        //noe med for løkke     
    //     hardware_command_door_open(1);

void states(void){
    State current_state = START_UP;
    while(1){
        switch (current_state)
        {
        case START_UP: 
            printf("startup\n");
            hardware_command_door_open(0);
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}      
            if (!hardware_read_floor_sensor(0)){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            }
            else if (hardware_read_floor_sensor(0)){current_state = IDLE;}
            break;

        case IDLE:
            printf("idle\n"); 
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(0);
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            poll_buttons();

            break;

        case MOVE_UP:
            printf("moveup\n");
            hardware_command_door_open(0);
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            poll_buttons();
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            //if(bestilling i current-etasje) {door_open}
            break;

        case MOVE_DOWN:
            printf("movedown\n");
            hardware_command_door_open(0);
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            poll_buttons();
            // if(floor==ordered_floor && current_direction==ordered_direction) {
            //     hardware_command_movement(HARDWARE_MOVEMENT_STOP); 
            //     current_state=DOOR_OPEN;
            //     }
            break;

        case DOOR_OPEN:
            printf("door\n");            
            hardware_command_door_open(1);
            obstruction_active();
			if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            poll_buttons();
            current_state=IDLE;
            break;

		case EMERGENCY_STOP:            
            printf("emergency stop\n");
            hardware_command_stop_light(1);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            emergency_stop_active();
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i){
                if (hardware_read_floor_sensor(i)){
                    hardware_command_door_open(1);
                    obstruction_active();
                }
            }
           //FJERNE ALT LYS
            clear_all_order_lights();
            hardware_command_stop_light(0);
            empty_matrix ();         //KØMATRISE SETTES TIL 0 = TØMMMES
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