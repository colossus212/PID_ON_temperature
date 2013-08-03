#include"defines.h"


#define  LCD_DataPortH P1     //高8位数据口,8位模式下只使用高8位 
#define  LCD_DataPortL P0     //低8位数据口	,8位模式下低8位可以不接线

sbit LCD_REST  = P3^3;    //RST 引脚定义
sbit LCD_RD   =  P3^2;	 //RD  引脚定义
sbit LCD_WR   =  P2^5;	 //WR  引脚定义
sbit LCD_RS   =  P2^6;	 //RS  引脚定义
sbit LCD_CS   =  P2^7;	 //CS  引脚定义 


#define  LCD_SIZE_X		240
#define  LCD_SIZE_Y		320

extern  uint16 colors[];

void LCD_Init(void);
//void LCD_ShowString(uint x,uint y,uint For_color,uint Bk_color,char *p);
//void LCD_ShowChar(uint x,uint y,uint For_color,uint Bk_color, char ch);
//void ChineseChar(uint x,uint y,int size,uint For_color,uint Bk_color ,char c);
void delaymsLCD(int count) ;
void LCD_Writ_Bus(char VH,char VL);
void LCD_Write_COM(char VH,char VL);
void LCD_Write_DATA(char VH,char VL);
void PantLCD(char VH,char VL);
void Address_setLCD(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCDLineDDA(int x0,int y0,int x1,int y1);


