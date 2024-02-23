#include<stdio.h>
#include "Timers.h"

// timer decrements 60 times her sec (60Hz)
int timer_freq = 60;

DataByte Delay_timer_val;
int d_initial_instruction_num;

DataByte Sound_timer_val;
int s_initial_instruction_num;

void set_delay_timer(DataByte val, int instruction_num){
	d_initial_instruction_num = instruction_num;
	Delay_timer_val = val;
}

DataByte get_delay_timer(int instruction_num){
	float diff = instruction_num - d_initial_instruction_num;
	float x = diff/FREQ;
	// printf("%f\n",x);
	Delay_timer_val -= timer_freq*(x);
	return Delay_timer_val;
}

void set_sound_timer(DataByte val, int instruction_num){
	s_initial_instruction_num = instruction_num;
	Sound_timer_val = val;
}

DataByte get_sound_timer(int instruction_num){
	float diff = instruction_num - s_initial_instruction_num;
	float x = diff/FREQ;
	// printf("%f\n",x);
	Sound_timer_val -= timer_freq*(x);
	return Sound_timer_val;
}


// int main(){
	// set_delay_timer(239,3);
	// printf("%d\n",get_delay_timer(100));
	// return 0;
// }
