#ifndef __5110__
#define __5110__

#include"STC_NEW_8051.h"
#include"defines.h"
sbit    sce = P2^5;  //Ƭѡ
sbit    res = P2^7;  //��λ,0��λ
sbit    dc  = P2^6;  //1д���ݣ�0дָ��
sbit    sdin = P3^3;  //����
sbit    sclk = P3^4;  //ʱ��

void delay_1ms5110(void);//1ms��ʱ����
void LCD_write_byte5110(unsigned char dt, unsigned char command);
void LCD_init5110(void);
void LCD_set_XY5110(unsigned char X, unsigned char Y);
void LCD_clear5110(void);
void DDALine5110(uint8 x0,uint8 y0,uint8 x1,uint8 y1);
void LCD_draw_point5110(unsigned char x, unsigned char y);

#endif


