#include<stdio.h>
#include "Memory.h"
#include "Registers.h"

void load(char* filename){
	FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
    }

    int byte;
    Address curr_addr = get_PC();
    while ((byte = fgetc(file)) != EOF) {
    	printf("%02x ",byte);
        write_mem(curr_addr,(DataByte)byte);
        curr_addr++;
    }
    // printf("%x\n",read_mem(get_PC()+1));

    fclose(file);
}

// int main(){
	// load("./ch8_files/IBM_logo.ch8");
	// Display_mem();
	// return 0;
// }
