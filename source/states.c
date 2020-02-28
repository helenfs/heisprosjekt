#include "states.h"


 void states(void){
    State current_state=START_UP;
    int current_floor;
    int motor_direction;
    int last_floor;
    int timer_trigger;
    int at_floor;
    
    while(1){
        current_floor=floor_indicator();
            at_floor=0;
            if (current_floor >=0){
                    at_floor=1;
                    last_floor = current_floor;
            }


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
            if (hardware_read_stop_signal()){
                current_state = EMERGENCY_STOP;
                break;
            }

            if(get_ordered_above(last_floor)>last_floor){
                if(motor_direction == motor_up){
                    current_state = MOVE_UP;
                }
                else if(motor_direction==motor_down){
                    motor_direction=motor_up;
                    current_state=MOVE_UP;
                }
            }

            else if(get_ordered_above(last_floor)==last_floor){
                if(at_floor == 1){
                    delete_order(last_floor, HARDWARE_ORDER_INSIDE);
                    delete_order(last_floor, HARDWARE_ORDER_UP);
                    delete_order(last_floor, HARDWARE_ORDER_DOWN);
                    timer_trigger=1;
                    current_state=DOOR_OPEN;
                }
                if(at_floor!=1){
                    if(motor_direction==motor_up){
                        while (current_floor==-1){
                            current_floor = floor_indicator();
                            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                        }
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        delete_order(current_floor, HARDWARE_ORDER_INSIDE);
                        delete_order(current_floor, HARDWARE_ORDER_UP);
                        delete_order(current_floor, HARDWARE_ORDER_DOWN);
                        timer_trigger=1;
                        current_state=DOOR_OPEN;
                        break;
                    }
                    else if(motor_direction==motor_down){
                        while (current_floor==-1){
                            current_floor = floor_indicator();
                            hardware_command_movement(HARDWARE_MOVEMENT_UP);
                        }
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        delete_order(current_floor, HARDWARE_ORDER_INSIDE);
                        delete_order(current_floor, HARDWARE_ORDER_UP);
                        delete_order(current_floor, HARDWARE_ORDER_DOWN);
                        timer_trigger=1;
                        current_state=DOOR_OPEN;
                    }
                }
            }

            else if(get_ordered_below(last_floor)<last_floor) {
                if(motor_direction == motor_down){
                    current_state=MOVE_DOWN;
                }
                else if(motor_direction == motor_up){
                    motor_direction=motor_down;
                    current_state = MOVE_DOWN;
                }
                
            }
            else {
                current_state = IDLE;
            }


            break;



        case MOVE_UP:
            printf("move up\n");
            poll_buttons();
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
			if (hardware_read_stop_signal()){
                current_state = EMERGENCY_STOP;
                break;
            }
            

            if(queue_matrix[current_floor][HARDWARE_ORDER_INSIDE]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                motor_direction = motor_up;
                delete_order(current_floor,HARDWARE_ORDER_INSIDE);
                timer_trigger = 1;
                current_state=DOOR_OPEN;
            }

            else if(queue_matrix[current_floor][HARDWARE_ORDER_UP]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                motor_direction = motor_up;
                delete_order(current_floor,HARDWARE_ORDER_UP);
                timer_trigger = 1;
                current_state=DOOR_OPEN;
            }

            else if(queue_matrix[current_floor][HARDWARE_ORDER_DOWN]==1 ){
                if (get_ordered_above(last_floor)> last_floor){
                    current_state = MOVE_UP;
                }
                else if(!(get_ordered_above(last_floor)>last_floor)){
                    motor_direction = motor_down;
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    delete_order(last_floor,HARDWARE_ORDER_DOWN);
                    timer_trigger = 1;
                    current_state=DOOR_OPEN;
                }

            }

            break;

        case MOVE_DOWN:
            printf("move down\n");
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            poll_buttons();
			if (hardware_read_stop_signal()){
                current_state = EMERGENCY_STOP;
                break;
            }


            if(queue_matrix[current_floor][HARDWARE_ORDER_INSIDE]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                motor_direction = motor_down;
                delete_order(current_floor,HARDWARE_ORDER_INSIDE);
                timer_trigger = 1;
                current_state=DOOR_OPEN;
            }

            else if(queue_matrix[current_floor][HARDWARE_ORDER_DOWN]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                motor_direction = motor_down;
                delete_order(current_floor,HARDWARE_ORDER_DOWN);
                timer_trigger = 1;
                current_state=DOOR_OPEN;
            }

            else if(queue_matrix[current_floor][HARDWARE_ORDER_UP]==1){
                if (get_ordered_below(last_floor) < last_floor){
                    printf("skal ignorere (gå opp)\n");
                    printf("skal ignorere (gå opp)\n");
                    printf("skal ignorere (gå opp)\n");
                    printf("skal ignorere (gå opp)\n");
                    printf("skal ignorere (gå opp)\n");
                    printf("skal ignorere (gå opp)\n");
                    printf("skal ignorere (gå opp)\n");
                    printf("skal ignorere (gå opp)\n");
                    printf("skal ignorere (gå opp)\n");
                    current_state = MOVE_DOWN;
                }
                else if(!(get_ordered_below(last_floor)<last_floor)){
                    motor_direction = motor_up;
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");
                    printf("skal stoppe (gå opp)\n");

                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    delete_order(last_floor,HARDWARE_ORDER_UP);
                    timer_trigger = 1;
                    current_state=DOOR_OPEN;
                }
            }
            break;
        
        case DOOR_OPEN:
            printf("door open\n");
           
            if (timer_trigger==1){
                set_timer();
               timer_trigger = 0;
               }           
            
            door_active();

            poll_buttons();
			if (hardware_read_stop_signal()){
                current_state = EMERGENCY_STOP;
                break;
                }

            printf("telt ferdig");

            if(motor_direction==motor_up){
                printf("første if");
                if(get_ordered_above(last_floor)==last_floor){
                    delete_order(last_floor, HARDWARE_ORDER_INSIDE);
                    delete_order(last_floor, HARDWARE_ORDER_DOWN);
                    delete_order(last_floor, HARDWARE_ORDER_UP);
                    current_state=DOOR_OPEN;
                    break;
                }
                else if(get_ordered_above(last_floor)>last_floor){
                    current_state=MOVE_UP;
                    break;
                }
                else if(get_ordered_below(last_floor)<last_floor){
                    motor_direction=motor_down;
                    current_state=MOVE_DOWN;
                    break;
                }
                else{current_state=IDLE;}

            }

            else if(motor_direction==motor_down){
                if(get_ordered_above(last_floor)==last_floor){
                    delete_order(last_floor, HARDWARE_ORDER_INSIDE);
                    delete_order(last_floor, HARDWARE_ORDER_DOWN);
                    delete_order(last_floor, HARDWARE_ORDER_UP);
                    current_state=DOOR_OPEN;
                    break;
                }
                else if(get_ordered_below(last_floor)<last_floor){
                    current_state=MOVE_DOWN;
                    break;
                }
                else if(get_ordered_above(last_floor)>last_floor){
                    motor_direction=motor_up;
                    current_state=MOVE_UP;
                    break;
                }
                else{
                    current_state=IDLE;
                }
            }
            
            break;

        case EMERGENCY_STOP:
            printf("emergency stop\n");
            emergency_stop_active();

            clear_all_order_lights();
            empty_all_orders ();  
            poll_buttons();

            printf("%d \n ", current_floor);

            
            if (hardware_read_floor_sensor(current_floor)){
                    timer_trigger = 1;
                    current_state=DOOR_OPEN;
            }


            else if(current_floor==-1){
                
                current_state = IDLE;
            }

            break;



        default:
            break;
        }
    }
 }