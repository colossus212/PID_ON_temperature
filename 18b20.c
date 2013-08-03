//���ú�����uint16 get_temp();
//����һ����λ�����¶�ֵ���һλΪС��ֵ
#include"18b20.h"
//�¶�ֵС�����ֶ��ձ�
const uchar table_tempfh[]={0,1,1,2,3,3,4,4,5,6,6,7,8,8,9,9};
/******************************************************
�������ƣ�delay18b20(uint num)
����ֵ����
������uint num ��ɫ����ֵ
���ã���ʱ
*******************************************************/
void delay18b20(uint16 num)
{ 
while(num--);
}
/******************************************************
�������ƣ�void Init_DS18B20(void)
����ֵ����
��������
���ã���ʼ��18B20
*******************************************************/ 
void Init_DS18B20(void)
{
char x=0;
DQ18b20=1;
delay18b20(10);//������ʱ
DQ18b20=0;
delay18b20(80);//��ʱ>480us 540us
DQ18b20=1; //�������� 15-60us
delay18b20(20);
x=DQ18b20;//������״̬ Ϊ0��λ�ɹ���Ϊ1�򲻳ɹ� 
delay18b20(30);
DQ18b20=1;//�ͷ�����
}
/******************************************************
�������ƣ�uchar ReadOneChar(void)
����ֵ��uchar dat
������ ��
���ã���1820һ���ֽ�
*******************************************************/
uchar ReadOneChar(void)
{
uchar i;
uchar dat=0;
for(i=0;i<8;i++)
{
DQ18b20=0;
dat>>=1;
DQ18b20=1;//������
if(DQ18b20) {dat|=0x80;}//��1 /// ��0���ƴ��� 
delay18b20(8);//15us�ڶ���һ����
}
return(dat);
}
/******************************************************
�������ƣ�void WriteOneChar(uchar dat)
����ֵ����
������ uchar dat
���ã�д1820һ���ֽ�
*******************************************************/
/////****дDS18B20***///д0 60us���꣬д1 30us �ڶ���
void WriteOneChar(uchar dat)
{
uchar i=0;
for(i=0;i<8;i++)
{
DQ18b20=0; 
DQ18b20=dat&0x01;//д�����������λ
delay18b20(10); ///////////
DQ18b20=1;//������
dat>>=1; 
}
delay18b20(8);
}
/******************************************************
�������ƣ�int ReadOneTemperature(void)
����ֵ��int t
������ ��
���ã����¶�ֵ
*******************************************************/
int get_temp(void) ////////***��ȡ�¶�ֵ***********///// ÿ�ζ�д��Ҫ�ȸ�λ
{ 
uchar a=0;
uchar b=0;
uint16 t=0;
Init_DS18B20();
WriteOneChar(0xcc);//������ROM����
WriteOneChar(0x44);//������ʼת������
Init_DS18B20();
WriteOneChar(0xcc);//������ROM����
WriteOneChar(0xbe);//���Ĵ����������ֽڣ�ǰ���ֽ�Ϊת��ֵ
a=ReadOneChar(); //a����ֽ�
b=ReadOneChar(); //b����ֽ�
t=((b<<8)|a);
return((t>>4)*10+table_tempfh[t&0x0f]);
/*
t=b;
t<<=8;//���ֽ�ת��Ϊ10����
t=t|a;
tep=t*0.0625;//ת������Ϊ0.0625/LSB
t=tep*10+0.5;//����1λС������������****�����10��ԭ��ȷ�¶�ֵ��
*/
}
//Function:�ڲ�����

void Config18b20 (void)  //�������ñ����޶�ֵ�ͷֱ���
{
     Init_DS18B20();
     WriteOneChar(0xcc);  //skip rom
     WriteOneChar(0x4e);  //write scratchpad
     WriteOneChar(0xff);  //����
     WriteOneChar(0x00);  //����
     WriteOneChar(0x7f);     //set 12 bit
     Init_DS18B20();
     WriteOneChar(0xcc);  //skip rom
     WriteOneChar(0x48);  //�����趨ֵ
     Init_DS18B20();
     WriteOneChar(0xcc);  //skip rom
     WriteOneChar(0xb8);  //�ص��趨ֵ
}

