#ifndef MEMORY_H_
#define MEMORY_H_
#include "CommonUtils.h"

DataByte read_mem(Address loc);
void write_mem(Address loc,DataByte val);
void Display_mem();

#endif
