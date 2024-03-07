#include<stdio.h>
#include "raylib.h"

int Wwidth = 64;
int Wheight = 32;
int PixelSize = 10;

void init(){
	InitWindow(800,450,"tutorial");
	int posX = 10;
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawRectangle(posX, 200, 100, 100, BLUE);
		EndDrawing();
	}
	CloseWindow();	
}

int main(){
	init();
	return 0;
}
