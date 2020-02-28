#include "light.h"

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
    //set_timer();
    while (check_timer()){          
        printf("dør åpen i 3 sek\n");
        hardware_command_door_open(1);
        poll_buttons();
        while (hardware_read_obstruction_signal() || hardware_read_stop_signal()){
            set_timer();
            poll_buttons();
            hardware_command_door_open(1);
            if (hardware_read_stop_signal()){
                hardware_command_stop_light(1);
                empty_all_orders();
                clear_all_order_lights();
            }
            hardware_command_stop_light(0);
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
