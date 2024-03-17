#ifndef FONTS_H_
#define FONTS_H_
#include "CommonUtils.h"

void getFontData(uint8_t hex_val, DataByte fdata[5]){
	switch(hex_val){
		case 0x0:
			fdata[0] = 0xF0;
			fdata[1] = 0x90;
			fdata[2] = 0x90;
			fdata[3] = 0x90;
			fdata[4] = 0xF0;
		break;
		case 0x1:
			fdata[0] = 0x20;
			fdata[1] = 0x60;
			fdata[2] = 0x20;
			fdata[3] = 0x20;
			fdata[4] = 0x70;
		break;
		case 0x2:
			fdata[0] = 0xF0;
			fdata[1] = 0x10;
			fdata[2] = 0xF0;
			fdata[3] = 0x80;
			fdata[4] = 0xF0;
		break;
		case 0x3:
			fdata[0] = 0xF0;
			fdata[1] = 0x10;
			fdata[2] = 0xF0;
			fdata[3] = 0x10;
			fdata[4] = 0xF0;
		break;
		case 0x4:
			fdata[0] = 0x90;
			fdata[1] = 0x90;
			fdata[2] = 0xF0;
			fdata[3] = 0x10;
			fdata[4] = 0x10;
		break;
		case 0x5:
			fdata[0] = 0xF0;
			fdata[1] = 0x80;
			fdata[2] = 0xF0;
			fdata[3] = 0x10;
			fdata[4] = 0xF0;
		break;
		case 0x6:
			fdata[0] = 0xF0;
			fdata[1] = 0x80;
			fdata[2] = 0xF0;
			fdata[3] = 0x90;
			fdata[4] = 0xF0;
		break;
		case 0x7:
			fdata[0] = 0xF0;
			fdata[1] = 0x10;
			fdata[2] = 0x20;
			fdata[3] = 0x40;
			fdata[4] = 0x40;
		break;
		case 0x8:
			fdata[0] = 0xF0;
			fdata[1] = 0x90;
			fdata[2] = 0xF0;
			fdata[3] = 0x90;
			fdata[4] = 0xF0;
		break;
		case 0x9:
			fdata[0] = 0xF0;
			fdata[1] = 0x90;
			fdata[2] = 0xF0;
			fdata[3] = 0x10;
			fdata[4] = 0xF0;
		break;
		case 0xA:
			fdata[0] = 0xF0;
			fdata[1] = 0x90;
			fdata[2] = 0xF0;
			fdata[3] = 0x90;
			fdata[4] = 0x90;
		break;
		case 0xB:
			fdata[0] = 0xE0;
			fdata[1] = 0x90;
			fdata[2] = 0xE0;
			fdata[3] = 0x90;
			fdata[4] = 0xE0;
		break;
		case 0xC:
			fdata[0] = 0xF0;
			fdata[1] = 0x80;
			fdata[2] = 0x80;
			fdata[3] = 0x80;
			fdata[4] = 0xF0;
		break;
		case 0xD:
			fdata[0] = 0xE0;
			fdata[1] = 0x90;
			fdata[2] = 0x90;
			fdata[3] = 0x90;
			fdata[4] = 0xE0;
		break;
		case 0xE:
			fdata[0] = 0xF0;
			fdata[1] = 0x80;
			fdata[2] = 0xF0;
			fdata[3] = 0x80;
			fdata[4] = 0xF0;
		break;
		case 0xF:
			fdata[0] = 0xF0;
			fdata[1] = 0x80;
			fdata[2] = 0xF0;
			fdata[3] = 0x80;
			fdata[4] = 0x80;
		break;
	}
}

#endif
