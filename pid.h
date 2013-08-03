#ifndef __PID__
#define __PID__

typedef struct PIDValue
{
uint32      Ek_Uint32[3];                  //差值保存，给定和反馈的差值
uint8       EkFlag_Uint8[3];              //符号，1则对应的为负数，0为对应的为正数     
uint8       KP_Uint8;
uint8       KI_Uint8;
uint8       KD_Uint8;
uint16      Uk_Uint16;                 //上一时刻的控制电压
uint16      RK_Uint16;                //设定值
uint16      CK_Uint16;               //实际值 
}PIDValueStr;
//PIDValueStr  PID;
void     PIDOperation (PIDValueStr *PID)  ;
#endif
