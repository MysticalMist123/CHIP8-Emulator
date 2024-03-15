#include<stdio.h>
#include "Timers.h"
#include <sys/time.h>

unsigned long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

// timer decrements 60 times her sec (60Hz)
int timer_freq = 60;

DataByte Delay_timer_val;
unsigned long d_initial_time;

DataByte Sound_timer_val;
unsigned long s_initial_time;

void set_delay_timer(DataByte val){
	// d_initial_instruction_num = instruction_num;
	d_initial_time = getMicrotime();
	Delay_timer_val = val;
}

DataByte get_delay_timer(){
	unsigned long curr_time = getMicrotime();
	unsigned long diff = curr_time - d_initial_time;
	Delay_timer_val -= (((unsigned long)timer_freq*diff)/(unsigned long)1000000);
	return Delay_timer_val;
}

void set_sound_timer(DataByte val){
	s_initial_time = getMicrotime();
	Sound_timer_val = val;
}

DataByte get_sound_timer(){
	unsigned long curr_time = getMicrotime();
	unsigned long diff = curr_time - s_initial_time;
	Sound_timer_val -= (((unsigned long)timer_freq*diff)/(unsigned long)1000000);
	return Sound_timer_val;
}


// int main(){
	// set_delay_timer(239,3);
	// printf("%d\n",get_delay_timer(100));
	// return 0;
// }
