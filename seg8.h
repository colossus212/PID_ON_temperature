#ifndef __SEG8__
#define __SEG8__

sbit SEG8SDA	=     P2^2;
sbit SEG8SHIFT_CP  =  P2^3;
sbit SEG8ST_CP     =  P2^4;
void seg8Disp(uint16 var,uchar rol,uchar pot);
void InitSerialPortSEG8(void);
void SerialSendDataSEG8(uint16 dat);
#endif
