#include "states.h"
#include <stdio.h>
#include <time.h>
#include "hardware.h"
#include "floor.h"
#include "timer.h"

#define motor_up 1
#define motor_down -1


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
    while(hardware_read_stop_signal()){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        hardware_command_stop_light(1);
        printf("read stop signal\n");
    }
    hardware_command_stop_light(0);
 
}
    
int door_active(void){
    set_timer();
    // while (check_timer()){          
    //     printf("dør åpen i 3 sek\n");
    //     hardware_command_door_open(1);
    //     poll_buttons();
    //     // while (hardware_read_obstruction_signal()){
    //     //     set_timer();
    //     //     poll_buttons();
    //     //     hardware_command_door_open(1);
    //     //     printf("tiden skal starte\n");
    //     // }
    // }
    hardware_command_door_open(0);  
    poll_buttons();
    return 1;
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


 void states(void){
    State current_state=START_UP;
    int current_floor;
    int motor_direction;
    int last_floor;
    
    while(1){
        current_floor=floor_indicator();
            if (current_floor >=0){
                    last_floor = current_floor;}


        switch (current_state) {
        
       
        case START_UP: 
            printf("startup\n");
            hardware_command_door_open(0);
            if (!hardware_read_floor_sensor(0)){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            }
            else if (hardware_read_floor_sensor(0)){
                motor_direction = motor_up;
                current_state = IDLE;

            }
            break;
        

        case IDLE:
            printf("idle\n");

            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(0);
            poll_buttons();
            //husk stoppknapp


            if(get_ordered_above(last_floor)>last_floor){
                current_state = MOVE_UP;
            }

            else if(get_ordered_above(last_floor)==last_floor){
                last_floor=DOOR_OPEN;
            }

            else if(get_ordered_below(last_floor)<last_floor){
                current_state=MOVE_DOWN;
            }
            else {
                current_state = IDLE;
            }


            break;



        case MOVE_UP:
            printf("move up\n");
            poll_buttons();
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            //stoppknapp

            if(queue_matrix[last_floor][HARDWARE_ORDER_INSIDE]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                motor_direction = motor_up;
                delete_order(last_floor,HARDWARE_ORDER_INSIDE);
                current_state=DOOR_OPEN;
            }

            else if(queue_matrix[last_floor][HARDWARE_ORDER_UP]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                motor_direction = motor_up;
                delete_order(last_floor,HARDWARE_ORDER_UP);
                current_state=DOOR_OPEN;
            }

            else if(queue_matrix[last_floor][HARDWARE_ORDER_DOWN]==1){
                if(!(get_ordered_above(last_floor)>last_floor)){
                    motor_direction = motor_down;
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    delete_order(last_floor,HARDWARE_ORDER_DOWN);
                    current_state=DOOR_OPEN;
                }
            }


        case MOVE_DOWN:
            printf("move down\n");
            poll_buttons();
            //stoppknapp
            if(queue_matrix[last_floor][HARDWARE_ORDER_INSIDE]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                motor_direction = motor_down;
                delete_order(last_floor,HARDWARE_ORDER_INSIDE);
                current_state=DOOR_OPEN;
            }

            else if(queue_matrix[last_floor][HARDWARE_ORDER_DOWN]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                motor_direction = motor_down;
                delete_order(last_floor,HARDWARE_ORDER_DOWN);
                current_state=DOOR_OPEN;
            }

            else if(queue_matrix[last_floor][HARDWARE_ORDER_UP]==1){
                if(!(get_ordered_below(last_floor)<last_floor)){
                    motor_direction = motor_up;
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    delete_order(last_floor,HARDWARE_ORDER_UP);
                    current_state=DOOR_OPEN;
                }
            }
        
        case DOOR_OPEN:
            printf("door open\n");
            door_active();
            poll_buttons();
            //stoppknapp

            //timer. Åpne dør.
            //slettte ordre

            if(motor_direction==motor_up){
                if(get_ordered_above(last_floor)==last_floor){
                    delete_order(last_floor, HARDWARE_ORDER_INSIDE);
                    delete_order(last_floor, HARDWARE_ORDER_DOWN);
                    delete_order(last_floor, HARDWARE_ORDER_UP);
                    current_state=DOOR_OPEN;
                }
                else if(get_ordered_above(last_floor)>last_floor){
                    current_state=MOVE_UP;
                }
                else if(get_ordered_below(last_floor)<last_floor){
                    motor_direction=motor_down;
                    current_state=MOVE_DOWN;
                }
            }

            else if(motor_direction==motor_down){
                if(get_ordered_above(last_floor)==last_floor){
                    delete_order(last_floor, HARDWARE_ORDER_INSIDE);
                    delete_order(last_floor, HARDWARE_ORDER_DOWN);
                    delete_order(last_floor, HARDWARE_ORDER_UP);
                    current_state=DOOR_OPEN;
                }
                else if(get_ordered_below(last_floor)<last_floor){
                    current_state=MOVE_DOWN;
                }
                else if(get_ordered_above(last_floor)>last_floor){
                    motor_direction=motor_up;
                    current_state=MOVE_UP;
                }
            }

            else{
                current_state=IDLE;
            }

        //case EMERGENCY_STOP:



        default:
            break;
        }
    }
 }