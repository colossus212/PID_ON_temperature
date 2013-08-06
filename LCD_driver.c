#include"STC_NEW_8051.h"
#include"LCD_driver.h"
//#include"chinese.h"
//#include"char.h"

uint16 colors[]=
{
  0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xffff  //��ɫ����
};


void LCD_Init(void)
{

    LCD_REST=1;
	    delaymsLCD(5);	
		LCD_REST=0;
		delaymsLCD(5);
		LCD_REST=1;
		delaymsLCD(5);
	
		LCD_CS =0;  //��Ƭѡʹ��
	
	LCD_Write_COM(0x00,0x10); LCD_Write_DATA(0x00,0x00); // Power Control 1  current consumption  STB		                                                                                                                                                                                                                                                       
	delaymsLCD(10);
	
	LCD_Write_COM(0x00,0x11); LCD_Write_DATA(0x00,0x1c); // Power Control 2 		                                                                                                                                                                                                                                                           
	LCD_Write_COM(0x00,0x12); LCD_Write_DATA(0x12,0x12); // Power Control 3  BT2-0, DC11-10, DC21-20, DC31-30 	
	
		                                                                                                                                                                                                                                            
	LCD_Write_COM(0x00,0x13); LCD_Write_DATA(0x00,0x41); // Power Control 4  DCR_EX=0, DCR2-0, GVD6-0  	
			                                                                                                                                                                                                                                            
	LCD_Write_COM(0x00,0x14); LCD_Write_DATA(0x40,0x50); // Power Control 5  VCOMG=0, VCM6-0, VCMR=0, VML6-0  	
			                                                                                                                                                                                                                                
	LCD_Write_COM(0x00,0x10); LCD_Write_DATA(0x08,0x00); // Power Control 1 
	
			                                                                                                                                                                                                                                                     
	LCD_Write_COM(0x00,0x11); LCD_Write_DATA(0x01,0x1c); // Power Control 2
		                                                                                                                                                                                                                                                             
	delaymsLCD(300);//300ms		                                                                                                                                                                                                                                                                                                 
	LCD_Write_COM(0x00,0x11); LCD_Write_DATA(0x03,0x1c); // Power Control 2
		                                                                                                                                                                                                                                                             
	delaymsLCD(300);//300ms					                                                                                                                                                                                                                                                                                                 
	LCD_Write_COM(0x00,0x11); LCD_Write_DATA(0x07,0x1c);  // Power Control 2
		                                                                                                                                                                                                                                                             
	delaymsLCD(300);//300ms					                                                                                                                                                                                                                                                                                                 
	LCD_Write_COM(0x00,0x11); LCD_Write_DATA(0x0f,0x1c);  // Power Control 2
		                                                                                                                                                                                                                                                             
	delaymsLCD(40);//600ms					                                                                                                                                                                                                                                                                                                 
	LCD_Write_COM(0x00,0x11); LCD_Write_DATA(0x0f,0x39);  // Power Control 2	                                                                                                                                                                                                                                                             
	delaymsLCD(60);//500ms				
		
	LCD_Write_COM(0x00,0x01); LCD_Write_DATA(0x01,0x28);  // Driver Output Control   
			     
	LCD_Write_COM(0x00,0x02); LCD_Write_DATA(0x01,0x00);  // LCD-Driving-Waveform Control  
				                                                                                                                                                                                                                                             
	LCD_Write_COM(0x00,0x03); LCD_Write_DATA(0x10,0x30);  // Entry Mode  
				                                                                                                                                                                                                                                                                 
	LCD_Write_COM(0x00,0x08); LCD_Write_DATA(0x08,0x08);  // Frame Cycle Control 
				                                                                                                                                                                                                                                                                             
	LCD_Write_COM(0x00,0x0b); LCD_Write_DATA(0x11,0x05);  // Frame Cycle Control
	                                                                                                                                                                                                                                                 
	LCD_Write_COM(0x00,0x0c); LCD_Write_DATA(0x00,0x00);  // External Display Interface Control 
	
	
	LCD_Write_COM(0x00,0x15); LCD_Write_DATA(0x00,0x20);   //VCI Recycling (R15H)		//		VCIR=010	 0X0020
	
	LCD_Write_COM(0x00,0x30); LCD_Write_DATA(0x00,0x00);   //		SCN 0	Start from G1	
		                                                                                                                                                                                                                                                                           
	LCD_Write_COM(0x00,0x34); LCD_Write_DATA(0x01,0x3f);   //		SE1 = 100111111( 319)	
		                                                                                                                                                                                                                                                                       
	LCD_Write_COM(0x00,0x35); LCD_Write_DATA(0x00,0x00);   //		SS1 = 000000000
		                                                                                                                                                                                                                                                                             
	LCD_Write_COM(0x00,0x36); LCD_Write_DATA(0x00,0xef);   //		HEA = 011101111(239)	
		                                                                                                                                                                                                                                                                       
	
	LCD_Write_COM(0x00,0x37); LCD_Write_DATA(0x00,0x00);   //		HSA = 000000000	
		                                                                                                                                                                                                                                                                             
	
	LCD_Write_COM(0x00,0x38); LCD_Write_DATA(0x01,0x3f);   //		VEA = 100111111( 319)
		                                                                                                                                                                                                                                                                       
	
	LCD_Write_COM(0x00,0x39); LCD_Write_DATA(0x00,0x00);  //		VSA = 000000000	
	
		                                                                                                                                                                                                                                                                             
	
	LCD_Write_COM(0x00,0x50); LCD_Write_DATA(0x01,0x01);  // Gamma Control   
			                                                                                                                                                                                                                                                                               
	LCD_Write_COM(0x00,0x51); LCD_Write_DATA(0x09,0x03);
		                                                                                                                                                                                                                                                                               
	LCD_Write_COM(0x00,0x52); LCD_Write_DATA(0x0b,0x08);
		                                                                                                                                                                                                                                                                               
	LCD_Write_COM(0x00,0x53); LCD_Write_DATA(0x08,0x05);
		                                                                                                                                                                                                                                                                               
	LCD_Write_COM(0x00,0x54); LCD_Write_DATA(0x01,0x01);	
		                                                                                                                                                                                                                                                                               
	LCD_Write_COM(0x00,0x55); LCD_Write_DATA(0x0d,0x06);
		                                                                                                                                                                                                                                                                               
	LCD_Write_COM(0x00,0x56); LCD_Write_DATA(0x0e,0x0a);
		                                                                                                                                                                                                                                                                               
	LCD_Write_COM(0x00,0x57); LCD_Write_DATA(0x01,0x00);
		                                                                                                                                                                                                                                                                               
	LCD_Write_COM(0x00,0x58); LCD_Write_DATA(0x1f,0x0b);
			                                                                                                                                                                                                                                                                               
	LCD_Write_COM(0x00,0x59); LCD_Write_DATA(0x02,0x01);
			                                                                                                                                                                                                                                                                               
	
	LCD_Write_COM(0x00,0x20); LCD_Write_DATA(0x00,0x00);  //Set RAM Address
		                                                                                                                                                                                                                                                                             
	
	LCD_Write_COM(0x00,0x21); LCD_Write_DATA(0x00,0x00);  //Set RAM Address		                                                                                                                                                                                                                                                                             
	//0x22			RAM Data Write		
	//LCD_CtrlWrite(0x0022);
							                                                                                                                                                                                                                                                                         
	LCD_Write_COM(0x00,0x0f); LCD_Write_DATA(0x1f,0x01);   // Start Oscillation   
	
    delaymsLCD(300);//300ms
	LCD_Write_COM(0x00,0x07); LCD_Write_DATA(0x00,0x16);  // Display Control   		                                                                                                                                                                                                                                                                         
	delaymsLCD(32);//200ms
	LCD_Write_COM(0x00,0x07); LCD_Write_DATA(0x00,0x17);
	
	LCD_CS =1; 
}  




void delaymsLCD(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<100;j++);
}

void LCD_Writ_Bus(char VH,char VL)   //��������д�뺯��
{
    LCD_DataPortH=VH;	  //��λP1��
	LCD_DataPortL=VL;	  //��λP0��	
	LCD_WR=0;
	LCD_WR=1; 
}



void LCD_Write_COM(char VH,char VL)	 //��������
{	
    LCD_RS=0;
	LCD_Writ_Bus(VH,VL);
}


void LCD_Write_DATA(char VH,char VL)	//��������
{
    LCD_RS=1;
	LCD_Writ_Bus(VH,VL);
}




	void PantLCD(char VH,char VL)
	{
	int i,j;
	LCD_CS =0;  //��Ƭѡʹ��
	Address_setLCD(0,0,239,319);
    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
        	 LCD_Write_DATA(VH,VL);
	    }

	  }
     LCD_CS =1;  //�ر�Ƭѡʹ��
}

/********************************************************************************************
	 DDA��Ϊ��ֵ΢�ֻ����㷨����ֱ�������㷨����򵥵�һ�֡�ԭ���൱�򵥣�������ֱ�۵ĸ���б�ʵ�
	 ƫ�Ƴ̶ȣ���������xΪ������������yΪ��������Ȼ������Ӧ�Ĳ��������ϣ���������ÿ������һ��
	 ���أ�����һ��������������ΪYk_1=Yk+m����xΪ��������Ϊ����mΪб�ʣ�
 ********************************************************************************************/

void LCDLineDDA(int x0,int y0,int x1,int y1)
{
	float dy,dx,x,y,m;
	LCD_CS=0;
    dx=x1-x0;
    dy=y1-y0;
    m=dy/dx;
    if(x0<x1)
    {
        if(m<=1&&m>=-1)
        {
              y=y0;
              for(x=x0;x<=x1;x++)
              {
                   Address_setLCD(x,y+0.5,x+1,y+1+0.5);
	               LCD_Write_DATA(0,255);
                  y+=m;
              }
        }
    }
    if(x0>x1)
    {
        if(m<=1&&m>=-1)
        {
              y=y0;
              for(x=x0;x>=x1;x--)
              {
               	   Address_setLCD(x,y+0.5,x+1,y+1+0.5);
	               LCD_Write_DATA(0,255);
                  y-=m;
              }
        }
    }
    if(y0<y1)
    {
        if(m>=1||m<=-1)
        {
              m=1/m;
              x=x0;
              for(y=y0;y<=y1;y++)
              {
              
				 Address_setLCD(x+0.5,y,x+1+0.5,y+1);
	               LCD_Write_DATA(0,255);
                  x+=m;
              }
        }
    }
    if(y0>y1)
    {
        if(m<=-1||m>=1)
        {
              m=1/m;
              x=x0;
              for(y=y0;y>=y1;y--)
              {
             
				   Address_setLCD(x+0.5,y,x+1+0.5,y+1);
	               LCD_Write_DATA(0,255);
                  x-=m;
              }
        }
    }
	LCD_CS=1;
}

void Address_setLCD(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{  
    LCD_Write_COM(0x00,0x20);LCD_Write_DATA(x1>>8,x1);	  //����X����λ��
    LCD_Write_COM(0x00,0x21);LCD_Write_DATA(y1>>8,y1);   //����Y����λ��

								 

    LCD_Write_COM(0x00,0x37);LCD_Write_DATA(x1>>8,x1);   //��ʼX
	LCD_Write_COM(0x00,0x39);LCD_Write_DATA(y1>>8,y1);	  //��ʼY
    LCD_Write_COM(0x00,0x36);LCD_Write_DATA(x2>>8,x2);   //����X
	LCD_Write_COM(0x00,0x38);LCD_Write_DATA(y2>>8,y2);   //����Y

	LCD_Write_COM(0x00,0x22);							 
}


/**********************************************************

  д�����Ӻ���

**********************************************************/
/*
void ChineseChar(uint x,uint y,int size,uint For_color,uint Bk_color ,char c)
{
   int e=0,i,j;
   int  ed;
   
   uint  ncols;
   uint  nrows;
   uint  nbytes;

   uchar *pfont;
   uchar *pchar;
   uchar *fonttable[]={(uchar *)hz16,(uchar *)hz24 , (uchar *)hz32};
   
   pfont=(uchar *)fonttable[size];

   if(size==0)
   {
     ncols =16-1;
     nrows =16-1;
     nbytes =32;	 //(16*16)/8
   }
   else
   if(size==1)
   {
     ncols =24-1;
     nrows =24-1;
     nbytes =72;  //(24*24)/8
   }
   else
   if(size==2)
   {
     ncols =32-1;
     nrows =32-1;
     nbytes =132;   //(32*32)/8
   }
   
   pchar=pfont + (nbytes*(c-1));

   Address_setLCD(x,  y, x+nrows,y+ncols);
   
   for(i=0;i<nbytes;i++)
   {
     ed=*pchar++;
	 if(size==0)
	 {
       if(i%2==0)
       e=8;
       else
       e=4;
	 }
	 else
	 e=8;
     
     for(j=0;j<e;j++)
     {// unsigned char temp;
	  if((ed>>j)&0x01)
      { 
       	//temp = 	For_color&0x00ff
	   LCD_Write_DATA(For_color>>8 , For_color  );  //textcolor
	  }
     else
     {
       LCD_Write_DATA( Bk_color>>8 ,  Bk_color);  //backcolor
	 }
	}
  }
}
*/
/*********************************************************/

/**********************************************************

  �ַ���ʾ�Ӻ���

**********************************************************/
/*
void LCD_ShowChar(uint x,uint y,uint For_color,uint Bk_color, char ch)
{       
   uchar temp , Bytes;
   uchar pos,t;
   uint  CHAR_W,CHAR_H;

   
   //CHAR_W = 8;         //8*16
   //CHAR_H = 16;

     CHAR_W = 16;         //16*24
     CHAR_H = 24;

   if(x>(LCD_SIZE_X-CHAR_W)||y>(LCD_SIZE_Y-CHAR_H))
   return;
   
   Address_setLCD(x, y, x+CHAR_W-1, y+CHAR_H-1);
   ch = ch-32;                       //����ASCII����˳��ĵ���Ӧ��ĸ�ı���
   Bytes = (CHAR_W*CHAR_H)/8;
   for(pos=0;pos<Bytes;pos++)  //CHAR_H 	(CHAR_W*CHAR_H)/8
   {
     // temp= Font8x16[ch][pos];

	  //temp= Font16x24[ch][pos];
	  temp= Font16x24[ch][pos];
      
      for(t=0;t<8;t++) //CHAR_W
      {                 
	    if(temp&0x80)
	    LCD_Write_DATA(For_color>>8 , For_color  );  //textcolor
	    else 
	    LCD_Write_DATA(Bk_color>>8 , Bk_color );  //backcolor
        temp<<=1; 
      }
	  
   }
}  
*/
/**********************************************************
 ��ʾ�ַ����Ӻ���

 x,y:�������  
 *p:�ַ�����ʼ��ַ

**********************************************************/
/*
void LCD_ShowString(uint x,uint y,uint For_color,uint Bk_color,char *p)
{         
   while(*p!='\0')
   {       
     LCD_ShowChar(x,y,For_color,Bk_color,*p);
    // x+=8;
	 x+=16;
     p++;
   }
}		    */
