#include<stdio.h>
#include "Memory.h"
#include "Stack.h"
#include "Registers.h"
#include "Timers.h"

int main(){
	// read_mem(4091);
	// write_mem(4091,4);
	// read_mem(4091);
	// Display_mem();
// 
	// s_push(1);
	// s_push(2);
	// s_push(3);
	// printf("%d\n",get_s_top());
	// s_pop();
	// printf("%d\n",get_s_top());
	// s_pop();
	// printf("%d\n",get_s_top());

	// printf("%x\n",get_index_register());
	// set_index_register(0xA12);
	// printf("%x\n",get_index_register());

	set_sound_timer(239,3);
	printf("%d\n",get_sound_timer(100));

	return 0;
}

