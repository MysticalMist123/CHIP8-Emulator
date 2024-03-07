#include<stdio.h>
#include "Memory.h"
#include "Registers.h"
#include "Stack.h"
#include "Timers.h"
#include "CommonUtils.h"
#include "raylib.h"
#define ON WHITE
#define OFF BLACK

int count = 0;
const int WinWidthPix = 64;
const int WinHeightPix = 32;
const int PixSize = 30;
const int WinWidth = WinWidthPix*PixSize;
const int WinHeight = WinHeightPix*PixSize;

void startCycle(){
	// initiate raylib window
	InitWindow(WinWidth,WinHeight,"Emulator");
	
	while(!WindowShouldClose()){ // raylib condition for close window
		// fetch instruction
		DataByte firstByte = read_mem(get_PC());
		DataByte secondByte = read_mem(get_PC()+1);

		DataByte FirstNib = firstByte>>4;
		DataByte SecondNib = firstByte&(0x0F);
		DataByte ThirdNib = secondByte>>4;
		DataByte FourthNib = secondByte&(0x0F);
		uint16_t SecNibSecByte = ((((0|SecondNib)<<4)|ThirdNib)<<4)|FourthNib;

		increment_PC();

		// decode and execute
		switch(FirstNib){
			case 0x0:
				switch(SecNibSecByte){
					case 0x0E0:  // 00E0 (clear screen)
						BeginDrawing();
						ClearBackground(OFF);
						EndDrawing();
					break;
				}
			break;
			case 0x1:
				set_PC(SecNibSecByte);  // 1NNN (jump)
			break;	
			case 0x6:
				set_general_register(secondByte,SecondNib);  // 6XNN (set register)
			break;
			case 0x7:  // 7XNN (add to register)
				set_general_register(get_general_register(SecondNib)+secondByte,SecondNib);
			break;
			case 0xA: // set index register
				set_index_register(SecNibSecByte);
			break;
			case 0xD: // draw a pixel
				
			break;
		}
	}
	// close raylib window
	CloseWindow();
}

int main(){
	// load CHIP8 instructions in memory
	startCycle();
	return 0;
}
