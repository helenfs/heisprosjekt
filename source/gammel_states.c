#include "states.h"
#include <stdio.h>
#include <time.h>
#include "hardware.h"
#include "floor.h"
#include "timer.h"

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
    while(hardware_read_stop_signal()){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        hardware_command_stop_light(1);
        printf("read stop signal\n");
    }
    hardware_command_stop_light(0);
 
}
    
int door_active(void){
    set_timer();
    
    
    while (check_timer()){           //difftime(clock(),time) <= 3000000.0
        printf("dør åpen i 3 sek\n");
        hardware_command_door_open(1);
        poll_buttons();
        while (hardware_read_obstruction_signal()){
            set_timer();
            poll_buttons();
            hardware_command_door_open(1);
            printf("tiden skal starte\n");
        }
     }
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
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i){
		for (int j = 0; j < 3; ++j) {
			queue_matrix[i][j] = 0;	
			printf("%d ", queue_matrix[i][j]);
		}
		printf("\n");
	}

    State current_state = START_UP;
    Elevator current_floor;
    Elevator motor_direction;
    while(1){

        current_floor.floor = floor_indicator();
                //delete_order(ordered_floor, order_type, i);
                   
        switch (current_state)
        {
        case START_UP: 
            printf("startup\n");
            hardware_command_door_open(0);
            if (!hardware_read_floor_sensor(0)){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            }
            else if (hardware_read_floor_sensor(0)){
                motor_direction.dir = HARDWARE_MOVEMENT_UP;
                current_floor.floor=0;
                current_state = IDLE;
                }
            break;

        case IDLE:
            printf("idle\n"); 
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(0);
            if (hardware_read_stop_signal()){
                poll_buttons();
                current_state = EMERGENCY_STOP;
            }
            poll_buttons();
            
         
            if(queue_order_above(current_floor.floor, motor_direction.dir)==1) {                    // Vi tror vi må endre dette!!
    
                  current_state=MOVE_UP;
            }
            

            if (queue_order_below(current_floor.floor, motor_direction.dir)==1){current_state=MOVE_DOWN;}

            if (!queue_order_above(current_floor.floor, motor_direction.dir) && !queue_order_below(current_floor.floor, motor_direction.dir)){current_state=IDLE;}


            //husk å legge til en fUnksjon med delete_order();
            break;


        case MOVE_UP:
            printf("%d\n",motor_direction.dir);
            hardware_command_door_open(0);            
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}

            poll_buttons();
            motor_direction.dir = HARDWARE_MOVEMENT_UP;
            if(!queue_matrix[current_floor.floor][HARDWARE_ORDER_UP] || !queue_matrix[current_floor.floor][HARDWARE_ORDER_INSIDE]){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }
            if(queue_matrix[current_floor.floor][HARDWARE_ORDER_UP]==1 || queue_matrix[current_floor.floor][HARDWARE_ORDER_INSIDE]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                delete_order(current_floor.floor,HARDWARE_ORDER_UP);
                delete_order(current_floor.floor,HARDWARE_ORDER_INSIDE);
                for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i){
		            for (int j = 0; j < 3; ++j) {	
			            printf("%d ", queue_matrix[i][j]);
                    }
		            printf("\n");
                }
                current_state=DOOR_OPEN;
            }


            break;


            //while (current_floor==1){hardware_command_movement(HARDWARE_MOVEMENT_STOP);}
            // while(queue_order_above(current_floor, HARDWARE_MOVEMENT_UP)){
            //     hardware_command_movement(HARDWARE_MOVEMENT_UP);
            //     printf("%d går oppover\n", current_floor);
            //     current_floor=floor_indicator();
            //     if(hardware_read_floor_sensor(current_floor)){
            //         printf("%d stoppp\n",current_floor);
            //         hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            //         current_state=DOOR_OPEN;
            //         break;
            //     }
            // }
            // printf("%d hei\n",current_floor);
            // hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            // // for(int i=0; i<HARDWARE_NUMBER_OF_FLOORS;++i){
            // //     if(i==current_floor && (queue_matrix[i][HARDWARE_ORDER_UP]==1 || queue_matrix[i][HARDWARE_ORDER_DOWN]==1 || queue_matrix[i][HARDWARE_ORDER_INSIDE])) {
            // //         hardware_command_movement(HARDWARE_MOVEMENT_STOP);                      //Hva om noen inni heisen bestiller en etasje??
            // //         current_state=DOOR_OPEN;
            // //     }
            // // }
        
            // break;

        case MOVE_DOWN:
            printf("movedown\n");
            hardware_command_door_open(0);
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            motor_direction.dir = HARDWARE_MOVEMENT_DOWN;
            if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            poll_buttons();

            if(!queue_matrix[current_floor.floor][HARDWARE_ORDER_DOWN] || !queue_matrix[current_floor.floor][HARDWARE_ORDER_INSIDE]){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            }
            if(queue_matrix[current_floor.floor][HARDWARE_ORDER_DOWN]==1 || queue_matrix[current_floor.floor][HARDWARE_ORDER_INSIDE]==1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                delete_order(current_floor.floor,HARDWARE_ORDER_DOWN);
                delete_order(current_floor.floor,HARDWARE_ORDER_INSIDE);
                current_state=DOOR_OPEN;
            }
            break;
            


        case DOOR_OPEN:
            printf("door\n");            
            hardware_command_door_open(1);
            obstruction_active();
			if (hardware_read_stop_signal()){current_state = EMERGENCY_STOP;}
            poll_buttons();
            if(obstruction_active()){
                current_state=IDLE;
            }
            break;

		case EMERGENCY_STOP:            
            printf("emergency stop\n");
            hardware_command_stop_light(1);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            emergency_stop_active();
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i){
                if (hardware_read_floor_sensor(i)){
                    hardware_command_door_open(1);
                    printf("åpne dør\n");
                    obstruction_active();
                }
            }
            clear_all_order_lights();
            hardware_command_stop_light(0);
            empty_all_orders ();  
            if(!queue_order_above(current_floor.floor,motor_direction.dir) || !queue_order_below(current_floor.floor,motor_direction.dir)){
                current_state=IDLE;
            }
            
            // while(floor_indicator()==-1){
            //     hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            
			break;
       
		default: 
			current_state=IDLE;	
        }
    }
}