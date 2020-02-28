#include "timer.h"


int waiting_time=3;

time_t our_timer;


void set_timer(){
	our_timer=time(NULL);
}


int check_timer(){
	if(our_timer + waiting_time > time(NULL)) { //our_timer.time + waiting_time > time(NULL)
		return 1;
	}
    return 0;
}

