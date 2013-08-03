#include"STC_NEW_8051.h"
#include"defines.h"
#include"18b20.h"
#include"uartTimer1.h"
#include"pid.h"
#include"seg8.h"
#include"LCD_driver.h"
#include<stdio.h>

sbit NOHOT=P2^1;
sbit KEY0=P3^7;
sbit KEY1=P3^6;

uint16 t5ms=0;
uint8 t1s=0;

void Timer0Init(void)		//5毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0xEE;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时

	ET0=1;
	EA=1;
}

void initAll()
{
	Init_DS18B20();
	Config18b20();
	UartInit();
	Timer0Init();
	InitSerialPortSEG8();
	LCD_Init();
	PantLCD(0x00,0x00);
}
void main()
{
	xdata PIDValueStr PID;
	uint16 t5ms_old=t5ms;
	uint8 pressed=0;
	uint8 added=0;
	uint8 x=0,y=0,x_o=0,y_o=0;
	initAll();
	printf("INIT OK!\n");
	PID.KP_Uint8=2;
	PID.KI_Uint8=2;
	PID.KD_Uint8=0;
	PID.RK_Uint16=400;//设定值
	while(1)
	{
		LCD_CS =0;
		LCDLineDDA(0,0,100,100);
		LCD_CS =1;
		if(t1s)
		{
			PID.CK_Uint16=get_temp();
			PIDOperation(&PID);
			printf("set temp:%d",PID.RK_Uint16);
			printf("set:%d",PID.Uk_Uint16);
			printf("temp:%d\n",PID.CK_Uint16);
			t1s=0;
			x_o=x;
			y_o=y;
			x=x_o+4;
			y=PID.CK_Uint16/4;
			LCDLineDDA(x_o,y_o,x,y);
		}
		//if(t5ms!=t5ms_old)
		if(t5ms%2)
		{
			//t5ms_old=t5ms;
			if(PID.Uk_Uint16>(uint16)t5ms/2)
			{
				NOHOT=0;
			}else
			{
				NOHOT=1;
			}
		}
		if(KEY0==0||KEY1==0)
		{
			if(pressed)
			{
				if(((t5ms>t5ms_old)&&(t5ms-t5ms_old>=2))||(t5ms<t5ms_old&&t5ms+200-t5ms_old>=2))
				{
					if(!added)
					{
						if(KEY0==0)
						{
							PID.RK_Uint16=PID.RK_Uint16+100;
						}
						if(KEY1==0)
						{
							PID.RK_Uint16=PID.RK_Uint16+10;
						}
					}
					added=1;
				}
			}else
			{
				
				pressed=1;
				t5ms_old=t5ms;
			}
		}
		if(KEY0==1&&KEY1==1)
		{
			added=0;
		}
		if(PID.RK_Uint16>900)
		{
			PID.RK_Uint16=400;
		}
		seg8Disp(PID.CK_Uint16,0,2);
		seg8Disp(PID.RK_Uint16,1,2);
	}
}

void timer0()interrupt 1
{
	t5ms++;
	if(t5ms>=200)
	{
		t5ms=0;
		t1s++;
	}
	TL0 = 0x00;		//设置定时初值
	TH0 = 0xEE;		//设置定时初值
}	 
