#ifndef __18B20__
#define __18B20__

#include"defines.h"
#include"STC_NEW_8051.h"

sbit DQ18b20=P2^0;

void delay18b20(uint16 num);
void Init_DS18B20(void);
uchar ReadOneChar(void);
void WriteOneChar(uchar dat);
int get_temp(void) ;
void Config18b20 (void);

#endif
