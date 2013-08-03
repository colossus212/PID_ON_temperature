//调用函数：uint16 get_temp();
//返回一个三位数的温度值最后一位为小数值
#include"18b20.h"
//温度值小数部分对照表
const uchar table_tempfh[]={0,1,1,2,3,3,4,4,5,6,6,7,8,8,9,9};
/******************************************************
函数名称：delay18b20(uint num)
返回值：无
参数：uint num 颜色数据值
作用：延时
*******************************************************/
void delay18b20(uint16 num)
{ 
while(num--);
}
/******************************************************
函数名称：void Init_DS18B20(void)
返回值：无
参数：无
作用：初始化18B20
*******************************************************/ 
void Init_DS18B20(void)
{
char x=0;
DQ18b20=1;
delay18b20(10);//稍作延时
DQ18b20=0;
delay18b20(80);//延时>480us 540us
DQ18b20=1; //拉高总线 15-60us
delay18b20(20);
x=DQ18b20;//读总线状态 为0复位成功，为1则不成功 
delay18b20(30);
DQ18b20=1;//释放总线
}
/******************************************************
函数名称：uchar ReadOneChar(void)
返回值：uchar dat
参数： 无
作用：读1820一个字节
*******************************************************/
uchar ReadOneChar(void)
{
uchar i;
uchar dat=0;
for(i=0;i<8;i++)
{
DQ18b20=0;
dat>>=1;
DQ18b20=1;//给脉冲
if(DQ18b20) {dat|=0x80;}//读1 /// 读0右移处理 
delay18b20(8);//15us内读完一个数
}
return(dat);
}
/******************************************************
函数名称：void WriteOneChar(uchar dat)
返回值：无
参数： uchar dat
作用：写1820一个字节
*******************************************************/
/////****写DS18B20***///写0 60us读完，写1 30us 内读完
void WriteOneChar(uchar dat)
{
uchar i=0;
for(i=0;i<8;i++)
{
DQ18b20=0; 
DQ18b20=dat&0x01;//写所给数据最低位
delay18b20(10); ///////////
DQ18b20=1;//给脉冲
dat>>=1; 
}
delay18b20(8);
}
/******************************************************
函数名称：int ReadOneTemperature(void)
返回值：int t
参数： 无
作用：读温度值
*******************************************************/
int get_temp(void) ////////***读取温度值***********///// 每次读写均要先复位
{ 
uchar a=0;
uchar b=0;
uint16 t=0;
Init_DS18B20();
WriteOneChar(0xcc);//发跳过ROM命令
WriteOneChar(0x44);//发读开始转换命令
Init_DS18B20();
WriteOneChar(0xcc);//发跳过ROM命令
WriteOneChar(0xbe);//读寄存器，共九字节，前两字节为转换值
a=ReadOneChar(); //a存低字节
b=ReadOneChar(); //b存高字节
t=((b<<8)|a);
return((t>>4)*10+table_tempfh[t&0x0f]);
/*
t=b;
t<<=8;//高字节转换为10进制
t=t|a;
tep=t*0.0625;//转换精度为0.0625/LSB
t=tep*10+0.5;//保留1位小数并四舍五入****后面除10还原正确温度值）
*/
}
//Function:内部配置

void Config18b20 (void)  //重新配置报警限定值和分辨率
{
     Init_DS18B20();
     WriteOneChar(0xcc);  //skip rom
     WriteOneChar(0x4e);  //write scratchpad
     WriteOneChar(0xff);  //上限
     WriteOneChar(0x00);  //下限
     WriteOneChar(0x7f);     //set 12 bit
     Init_DS18B20();
     WriteOneChar(0xcc);  //skip rom
     WriteOneChar(0x48);  //保存设定值
     Init_DS18B20();
     WriteOneChar(0xcc);  //skip rom
     WriteOneChar(0xb8);  //回调设定值
}

