#include<stdio.h>
#include<stdint.h>
typedef uint8_t DataByte;
typedef uint16_t Address; // 12-bit addresses only allowed
// 12 bit memory

DataByte memoryArray[4096];

DataByte read_mem(Address loc){
	return memoryArray[loc];
}

void write_mem(Address loc,DataByte val){
	memoryArray[loc] = val;
}

void Display_mem(){
	for(int i=0;i<4096;i++){
		printf("\n%x (%d) has %x (%d)\n",i,i,memoryArray[i],memoryArray[i]);
	}
}

// int main(){
	// while(1){
		// int res;
		// printf("\nInstruction: ");
		// scanf("%d",&res);
		// printf("\n");
		// if(res == 1){
			// Address loc;
			// scanf("%hd",&loc);
			// printf("\n%d\n",read_mem(loc));
		// }
		// else if(res == 2){
			// DataByte data;
			// printf("\ndata: ");
			// scanf("%hhd",&data);
			// Address loc;
			// printf("\nloc: ");
			// scanf("%hd",&loc);
			// write_mem(loc,data);
		// }
		// else{
			// Display_mem();
		// }
	// }
	// return 0;
// }
