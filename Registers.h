#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "CommonUtils.h"

void set_general_register(DataByte val, int index);
DataByte get_general_register(uint8_t index);
Address get_index_register();
void set_index_register(Address val);
void increment_PC();
Address get_PC();
void set_PC(Address val);

#endif
