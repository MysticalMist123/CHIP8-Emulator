#ifndef TIMERS_H_
#define TIMERS_H_
#include "CommonUtils.h"

void set_delay_timer(DataByte val, int instruction_num);
DataByte get_delay_timer(int instruction_num);
void set_sound_timer(DataByte val, int instruction_num);
DataByte get_sound_timer(int instruction_num);

#endif
