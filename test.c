#include<stdio.h>
#include "Memory.h"

int main(){
	read_mem(4091);
	write_mem(4091,4);
	read_mem(4091);
	Display_mem();
	return 0;
}
