#ifndef MEMORY_H_
#define MEMORY_H_
#include<stdint.h>

typedef uint8_t DataByte;
typedef uint16_t Address; // 12-bit addresses only allowed

DataByte read_mem(Address loc);
void write_mem(Address loc,DataByte val);
void Display_mem();

#endif
