#include "timer.h"


int waiting_time=3;



timer our_timer;

void set_timer(){
	our_timer.time=time(NULL);
}


int check_timer(){
	if(our_timer.time + waiting_time > time(NULL) || hardware_read_stop_signal() || hardware_read_obstruction_signal()) {
		if(hardware_read_stop_signal() || hardware_read_obstruction_signal()) {
			set_timer();
        }
		return 1;
	}
    return 0;
}