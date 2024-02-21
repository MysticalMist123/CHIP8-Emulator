#include<stdio.h>
// #include "Memory.h"
#include "Registers.h"

Address PC_register = 0x200;
Address index_register;
DataByte general_registers[16];

void set_general_register(DataByte val, int index){
	general_registers[index] = val;
}

DataByte get_general_register(uint8_t index){
	return general_registers[index];
}

Address get_index_register(){
	return index_register;
}

void set_index_register(Address val){
	index_register = val;
}

void increment_PC(){
	if(PC_register==0xFFF) PC_register=0;
	else PC_register++;
}

Address get_PC(){
	return PC_register;
}

// int main(){
	// printf("%x\n",get_index_register());
	// set_index_register(0xA12);
	// printf("%x\n",get_index_register());
// 
	// return 0;
// }
