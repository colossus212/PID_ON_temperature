#ifndef __PID__
#define __PID__

typedef struct PIDValue
{
uint32      Ek_Uint32[3];                  //��ֵ���棬�����ͷ����Ĳ�ֵ
uint8       EkFlag_Uint8[3];              //���ţ�1���Ӧ��Ϊ������0Ϊ��Ӧ��Ϊ����     
uint8       KP_Uint8;
uint8       KI_Uint8;
uint8       KD_Uint8;
uint16      Uk_Uint16;                 //��һʱ�̵Ŀ��Ƶ�ѹ
uint16      RK_Uint16;                //�趨ֵ
uint16      CK_Uint16;               //ʵ��ֵ 
}PIDValueStr;
//PIDValueStr  PID;
void     PIDOperation (PIDValueStr *PID)  ;
#endif
