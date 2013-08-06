#ifndef __5110__
#define __5110__

#include"STC_NEW_8051.h"
#include"defines.h"
sbit    sce = P2^5;  //片选
sbit    res = P2^7;  //复位,0复位
sbit    dc  = P2^6;  //1写数据，0写指令
sbit    sdin = P3^3;  //数据
sbit    sclk = P3^4;  //时钟

void delay_1ms5110(void);//1ms延时函数
void LCD_write_byte5110(unsigned char dt, unsigned char command);
void LCD_init5110(void);
void LCD_set_XY5110(unsigned char X, unsigned char Y);
void LCD_clear5110(void);
void DDALine5110(uint8 x0,uint8 y0,uint8 x1,uint8 y1);
void LCD_draw_point5110(unsigned char x, unsigned char y);

#endif


