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
const int PixSize = 10;
const int WinWidth = WinWidthPix*PixSize;
const int WinHeight = WinHeightPix*PixSize;
uint8_t Screen[32][64];

void startCycle(){
// NOTE: Pls use a matrix to keep track of display
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
						for(int i=0;i<WinHeightPix;i++){
							for(int j=0;j<WinWidthPix;j++){
								Screen[i][j] = 0;
							}
						}
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
			case 0xD: // draw
				DataByte x = get_general_register(SecondNib) % WinWidthPix;	
				DataByte y = get_general_register(ThirdNib) % WinHeightPix;
				set_general_register(0,0xF);
				Address sprite_row_addr = get_index_register();
				for(int i=0;i<FourthNib;i++){
					DataByte curr_sprite_row = read_mem(sprite_row_addr+i);
					if(y+i<WinHeightPix){
						for(int j=0;j<8;j++){
							if(x+j<WinWidthPix){
								uint8_t ScreenPixel = Screen[y+i][x+j];
								uint8_t SpritePixel = ((curr_sprite_row >> (8-j-1)) & 1);
								Screen[y+i][x+j] = (ScreenPixel ^ SpritePixel);
								if((ScreenPixel & SpritePixel)) set_general_register(1,0xF);

								// drawing the pixel at (x+j,y+i)
								BeginDrawing();
								DrawRectangle(x+j, y+i, PixSize, PixSize, Screen[y+i][x+j] == 0?OFF:ON);
								EndDrawing();
							}
							else break;
						}
					}
					else break;
				}
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
