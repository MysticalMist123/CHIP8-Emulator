#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include "Memory.h"
#include "Registers.h"
#include "Stack.h"
#include "Loader.h"
#include "Timers.h"
#include "CommonUtils.h"
#include "raylib.h"
#include "keyBindings.h"
// #include "fonts.h"
#define ON WHITE
#define OFF BLACK

char* filename = "./ch8_files/Pong.ch8";
// int count = 0;
const int WinWidthPix = 64;
const int WinHeightPix = 32;
const int PixSize = 10;
const int WinWidth = WinWidthPix*PixSize;
const int WinHeight = WinHeightPix*PixSize;
uint8_t Screen[32][64];

int getXFromMatrixIndex(int x_index){
	return x_index*PixSize;
}
int getYFromMatrixIndex(int y_index){
	return y_index*PixSize;
}

void startCycle(){
// NOTE: Pls use a matrix to keep track of display
	// initiate raylib window
	InitWindow(WinWidth,WinHeight,"Emulator");
	SetTargetFPS(60);
	while(1){
		if(get_PC()>0xFFF){
			break;
		}
		// printf("%03x\n",get_PC());
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
					case 0x0EE:
						set_PC(s_pop());
					break;
				}
			break;
			case 0x1:
				set_PC(SecNibSecByte);  // 1NNN (jump)
			break;
			case 0x2:
				s_push(get_PC());
				set_PC(SecNibSecByte);
			break;	
			case 0x3:
				if(get_general_register(SecondNib)==secondByte) increment_PC();
			break;
			case 0x4:
				if(get_general_register(SecondNib)!=secondByte) increment_PC();				
			break;
			case 0x5:
				if(get_general_register(SecondNib)==get_general_register(ThirdNib)) increment_PC();
			break;
			case 0x6:
				set_general_register(secondByte,SecondNib);  // 6XNN (set register)
			break;
			case 0x7:  // 7XNN (add to register)
				set_general_register(get_general_register(SecondNib)+secondByte,SecondNib);
			break;
			case 0x8:
				int X = get_general_register(SecondNib);
				int Y = get_general_register(ThirdNib);
				switch(FourthNib){
					case 0x0:
						set_general_register(Y,SecondNib);
					break;
					case 0x1:
						set_general_register((X|Y),SecondNib);
					break;
					case 0x2:
						set_general_register((X&Y),SecondNib);						
					break;
					case 0x3:
						set_general_register((X^Y),SecondNib);
					break;
					case 0x4:
						if(X+Y>0xFF) set_general_register(1,0xF);
						else set_general_register(0,0xF);
						set_general_register(X+Y,SecondNib);
					break;
					case 0x5: 
						if(X>Y) set_general_register(1,0xF);
						else if(Y>X && X-Y<0) set_general_register(0,0xF);
						set_general_register(X-Y,SecondNib);
					break;
					case 0x6: // CHIP-48 version
						set_general_register((X&1),0xF); // for COSMAC-VIP, replace X with Y
						set_general_register((X>>1),SecondNib); // for COSMAC-VIP, replace X with Y
					break;
					case 0x7:
						if(Y>X) set_general_register(1,0xF);
						else if(X>Y && Y-X<0) set_general_register(0,0xF);
						set_general_register(Y-X,SecondNib);
					break;
					case 0xE: // CHIP-48 version
						set_general_register(((X>>7)&1),0xF); // for COSMAC-VIP, replace X with Y
						set_general_register((X<<1),SecondNib); // for COSMAC-VIP, replace X with Y
					break;
				}
			break;
			case 0x9:
				if(get_general_register(SecondNib)!=get_general_register(ThirdNib)) increment_PC();				
			break;
			case 0xA: // set index register
				set_index_register(SecNibSecByte);
			break;
			case 0xB: // CHIP-48 version
				set_PC(SecNibSecByte+get_general_register(SecondNib));
			break;
			case 0xC:
				set_general_register(((rand()%(secondByte)) & secondByte),SecondNib);
			break;
			case 0xD: // draw
				BeginDrawing();
				DataByte x = (get_general_register(SecondNib)) % WinWidthPix;	
				DataByte y = (get_general_register(ThirdNib)) % WinHeightPix;
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
								// if(ScreenPixel==1 && SpritePixel==1){
									// Screen[y+i][x+j] = 0;
									// set_general_register(1,0xF);
								// }
								// else if(SpritePixel==1 && ScreenPixel==0){
									// Screen[y+i][x+j] = 1;
								// }

								// drawing the pixel at (x+j,y+i)
								DrawRectangle(getXFromMatrixIndex(x+j), getYFromMatrixIndex(y+i), PixSize, PixSize, Screen[y+i][x+j] == 0?OFF:ON);
							}
							else break;
						}
					}
					else break;
				}
				EndDrawing();
			break;
			case 0xE:
				switch(secondByte){
					case 0x9E:
						int key = toKey(get_general_register(SecondNib));
						if(IsKeyDown(key)) increment_PC();
					break;
					case 0xA1:
						key = toKey(get_general_register(SecondNib));
						if(IsKeyUp(key)) increment_PC(); // if problematic, use !isKeyDown
					break;
				}
			break;
			case 0xF:
				switch(secondByte){
					case 0x07:
						set_general_register(get_delay_timer(),SecondNib);
					break;
					case 0x15:
						set_delay_timer(get_general_register(SecondNib));
					break;
					case 0x18:
						set_sound_timer(get_general_register(SecondNib));
					break;
					case 0x1E:
						if(get_index_register()+get_general_register(SecondNib)>0xFFF) set_general_register(1,0xF);
						set_index_register(get_index_register()+get_general_register(SecondNib));
					break;
					case 0x0A:
						int k = GetKeyPressed();
						if(k){
							set_general_register(toCh8Key(k),SecondNib);
						}
						else set_PC(get_PC()-2);
					break;
					case 0x29:
						set_index_register(FONT_ADDR + 5*(get_general_register(SecondNib)));
					break;
					case 0x33:
						uint8_t val = get_general_register(SecondNib);
						write_mem(get_index_register()+2,val%10);
						write_mem(get_index_register()+1,(val/10)%10);
						write_mem(get_index_register(),val/100);
					break;
					case 0x55: // CHIP-48 implementation
						for(int i=0;i<=SecondNib;i++){
							write_mem(get_index_register()+i,get_general_register(i));
						}
					break;
					case 0x65: // CHIP-48 implementation
						for(int i=0;i<=SecondNib;i++){
							set_general_register(read_mem(get_index_register()+i),i);
						}
					break;					
				}
			break;
		}
		// for(int  i=0;i<WinHeightPix;i++){
			// for(int j=0;j<WinWidthPix;j++){
				// // printf("%d ",Screen[i][j]);
				// BeginDrawing();
				// DrawRectangle(getXFromMatrixIndex(j), getYFromMatrixIndex(i), PixSize, PixSize, Screen[i][j] == 0?OFF:ON);
				// EndDrawing();
			// }
			// // printf("\n");
		// }
		// printf("\n");
		// count++;
		usleep(1000000/FREQ);
	}
	// close raylib window
	CloseWindow();
}

int main(){
	// load CHIP8 instructions in memory
	srand((unsigned int)time(NULL));
	load(filename);
	startCycle();
	return 0;
}
