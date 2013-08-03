#include"STC_NEW_8051.h"
#include <intrins.h>
#include"defines.h"
#include"seg8.h"
#define SEG8NOP _nop_()
uchar code wei[]=
{0x01,0x02,0x04,0x08,
 0x10,0x20,0x40,0x80
};
uchar code duan[]={
   0xc0,0xf9,0xa4,0xb0,
   0x99,0x92,0x82,0xf8,
   0x80,0x90
         }; 

void InitSerialPortSEG8(void)
{
  SEG8SDA = 0;
  SEG8SHIFT_CP = 0;
  SEG8ST_CP = 0;
}

void SerialSendDataSEG8(uint16 dat)
{
  uchar ii;
  uint16 SEG8SDAta=dat;
  for(ii=0;ii<16;ii++)
  {
    if(SEG8SDAta&0x8000)SEG8SDA=1;
	else SEG8SDA = 0;
    SEG8SDAta<<=1;
    SEG8SHIFT_CP =0;
    SEG8NOP;
    SEG8NOP;
    SEG8SHIFT_CP = 1;
    SEG8NOP;
    SEG8NOP;
  }
  SEG8ST_CP = 1;
  SEG8NOP;
  SEG8NOP;
  SEG8ST_CP = 0;
}

void seg8Disp(uint16 var,uchar rol,uchar pot)
{
	unsigned int dx;
	uint8 i=0,tag=0;
	uint8 shu[4];
	shu[0]=var/1000;
	shu[1]=(var%1000)/100;
	shu[2]=(var%100)/10;
	shu[3]=var%10;
	
	InitSerialPortSEG8();
	
	if(rol)
	{
		tag=4;
	}else
	{
		tag=0;
	}
	for(i=tag;i<=3+tag;i++)
	{
		dx=wei[i];
		 if(pot==i%4)
		 {
		 dx=((dx<<8)|duan[shu[i%4]]&0x7f);
		 }
		 else
		 {
		 dx=((dx<<8)|duan[shu[i%4]]);
		 }
		 SerialSendDataSEG8(dx);
	}
	SerialSendDataSEG8(0xff);
}
