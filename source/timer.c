#include "timer.h"


int waiting_time=3;



timer our_timer;

void set_timer(){
	our_timer.time=time(NULL);
}


int check_timer(){
	if(time(NULL) - our_timer.time <3 || hardware_read_stop_signal() || hardware_read_obstruction_signal()) { //our_timer.time + waiting_time > time(NULL)
		if(hardware_read_stop_signal() || hardware_read_obstruction_signal()) {
			set_timer();
        }
		return 1;
	}
    return 0;
}

int check_time_difference(){
	return time(NULL) - our_timer.time;
}