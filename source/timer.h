#include <time.h>
#include "hardware.h"



typedef struct {
	time_t time;	
} timer;




void set_timer();
int check_timer();
int check_time_difference();