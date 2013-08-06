#include"5110.h"
#include"defines.h"
void delay_1ms5110(void)//1ms延时函数
{
	unsigned int i;
	for (i=0;i<500;i++)	  ;
;
}

/*--------------------------------------------
LCD_write_byte5110: 使用SPI接口写数据到LCD
输入参数：dt：写入的数据；
command ：写数据/命令选择；
编写日期：20080918 
----------------------------------------------*/
void LCD_write_byte5110(unsigned char dt, unsigned char command)
{
	unsigned char i; 
	sce=0;	
	dc=command;	
	for(i=0;i<8;i++)
	{ 
		if(dt&0x80)
			sdin=1;
		else
			sdin=0;
		dt=dt<<1;		
		sclk=0; 		
		sclk=1; 
	}	
	dc=1;	
	sce=1;	
	sdin=1;
}
/*---------------------------------------
LCD_init5110: 3310LCD初始化
编写日期：20080918 
-----------------------------------------  */
void LCD_init5110(void)
{
	res=0;  	
  	delay_1ms5110();
  	res=1;  
	LCD_write_byte5110(0x21,0);//初始化Lcd,功能设定使用扩充指令
	LCD_write_byte5110(0xc0,0);//设定液晶偏置电压d0
	LCD_write_byte5110(0x20,0);//使用基本指令
	LCD_write_byte5110(0x0C,0);//设定显示模式，正常显示
}
/*-------------------------------------------
LCD_set_XY5110: 设置LCD坐标函数
输入参数：X：0－83  Y：0－5
编写日期：20080918 
---------------------------------------------*/
void LCD_set_XY5110(unsigned char X, unsigned char Y)
{
	LCD_write_byte5110(0x40 | Y, 0);// column
	LCD_write_byte5110(0x80 | X, 0);// row
} 
/*------------------------------------------
LCD_clear5110: LCD清屏函数
编写日期：20080918 
--------------------------------------------*/
void LCD_clear5110(void)
{
	unsigned char t;
	unsigned char k;
	LCD_set_XY5110(0,0);
	for(t=0;t<6;t++)
	{ 
		for(k=0;k<84;k++)
		{ 
			LCD_write_byte5110(0x00,1);
				
		} 
	}
}/*-----------------------------------------------------------------------
LCD_draw_point(unsigned char x,unsigned char y)        : 任意位置画点函数

输入参数：x       ：0－83
          y       ：0－47

编写日期          ：2011-6-9 
最后修改日期      ：2011-6-9
by_menglongfc_fc.xxzj@gmail.com 
-----------------------------------------------------------------------*/
void LCD_draw_point5110(unsigned char x, unsigned char y)
{
	unsigned char X,Y,tmp;

	X = x;
	Y = y/8;
	tmp = 0x01 << y%8;
	LCD_set_XY5110(X,Y);
	LCD_write_byte5110(tmp,1);
}

/*-----------------------------------------------------------------------
void LCD_draw_line(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1)
函数功能          ：实现任意两点间画直线

输入参数：x0，x1  ：0－83
          y1，y1  ：0－47

编写日期          ：2011-6-9 
最后修改日期      ：2011-6-9
by_menglongfc_fc.xxzj@gmail.com 
-----------------------------------------------------------------------*/
//需修正首末点数值大小点问题
void DDALine5110(uint8 x0,uint8 y0,uint8 x1,uint8 y1)
{
    char dx,dy,n,k;
	float xinc,yinc,x,y;
	uint8 absdx,absdy;
    dx=x1-x0;dy=y1-y0;
	if(dx>=0)
	{
		absdx=dx;
	}else
	{
		absdx=-dx;
	}
	if(dy>=0)
	{
		absdy=dy;
	}else
	{
		absdy=-dy;
	}
    if (absdx>absdy)
        n=absdx;
    else
        n=absdy;
    xinc=(float)dx/n;
        yinc=(float)dy/n;
    x=(float)x0;y=(float)y0;
    for (k=1;k<=n;k++)
    {
        LCD_draw_point5110((int)(x+0.5),(int)(y+0.5));
            x+=xinc;
                y+=yinc;
    }
}	
