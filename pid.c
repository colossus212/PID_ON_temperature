#include"defines.h"
#include"PID.h"
const unsigned int MAXOUT=200;
//================================================================
// PID->H
// Operation about PID algorithm procedure 
// C51������  Keil 7.08
//================================================================
// ����:zhoufeng
// Date :2007-08-06
// All rights reserved.
//================================================================

uint8        out ;                 // �������
uint8        count;               // ���ʱ�䵥λ������
/*********************************
PID = Uk + KP*[E(k)-E(k-1)]+KI*E(k)+KD*[E(k)-2E(k-1)+E(k-2)];(������PID��ʽ)
�������: RK(�趨ֵ),CK(ʵ��ֵ),KP,KI,KD
��������: U(K)
//PID���㺯��
********************************/
void     PIDOperation (PIDValueStr *PID)  
{ 
uint32       Temp[3];                                        //�м���ʱ����
uint32       PostSum;                                       //������
uint32       NegSum;                                       //������
Temp[0] = 0;
Temp[1] = 0;
Temp[2] = 0;
PostSum = 0;
NegSum  = 0;
if( PID->RK_Uint16 > PID->CK_Uint16 )                    //�趨ֵ����ʵ��ֵ��
{
  if( PID->RK_Uint16 - PID->CK_Uint16 >100 )            //ƫ�����10��
  {
   PID->Uk_Uint16 = MAXOUT;    }                        //ƫ�����10Ϊ���޷�ֵ���(ȫ�ټ���)
  else
  {
   Temp[0] = PID->RK_Uint16 - PID->CK_Uint16;       //ƫ��<=10,����E(k)
   PID->EkFlag_Uint8[1]=0;                        //E(k)Ϊ����
   //��ֵ��λ
      PID->Ek_Uint32[2] = PID->Ek_Uint32[1];
      PID->Ek_Uint32[1] = PID->Ek_Uint32[0];
      PID->Ek_Uint32[0] = Temp[0];
/****************************************/
      if( PID->Ek_Uint32[0] >PID->Ek_Uint32[1] )                            //E(k)>E(k-1)��
      {
  Temp[0]=PID->Ek_Uint32[0] - PID->Ek_Uint32[1];           //E(k)>E(k-1)
        PID->EkFlag_Uint8[0]=0;  }                                       //E(k)-E(k-1)Ϊ����
   else
{
  Temp[0]=PID->Ek_Uint32[0] - PID->Ek_Uint32[1];        //E(k)<E(k-1)
        PID->EkFlag_Uint8[0]=1;  }                                               //E(k)-E(k-1)Ϊ����
/****************************************/
      Temp[2]=PID->Ek_Uint32[1]*2 ;                                             // 2E(k-1)
if( (PID->Ek_Uint32[0]+ PID->Ek_Uint32[2])>Temp[2] )            //E(k-2)+E(k)>2E(k-1)��
      {
  Temp[2]=(PID->Ek_Uint32[0]+ PID->Ek_Uint32[2])-Temp[2];     //E(k-2)+E(k)>2E(k-1)
        PID->EkFlag_Uint8[2]=0;  }                                          //E(k-2)+E(k)-2E(k-1)Ϊ����
   else
{
  Temp[2]=Temp[2]-(PID->Ek_Uint32[0]+ PID->Ek_Uint32[2]);  //E(k-2)+E(k)<2E(k-1)
        PID->EkFlag_Uint8[2]=1;  }                                       //E(k-2)+E(k)-2E(k-1)Ϊ����
/****************************************/       
      Temp[0] = (uint32)PID->KP_Uint8 * Temp[0];                        // KP*[E(k)-E(k-1)]
      Temp[1] = (uint32)PID->KI_Uint8 * PID->Ek_Uint32[0];              // KI*E(k)
      Temp[2] = (uint32)PID->KD_Uint8 * Temp[2];                      // KD*[E(k-2)+E(k)-2E(k-1)]

/*���²��ִ����ǽ����е���������ӣ����������*/     
/**********KP*[E(k)-E(k-1)]**********/
if(PID->EkFlag_Uint8[0]==0)
  PostSum += Temp[0];                                    //������
else                                              
  NegSum += Temp[0];                                    //������
/********* KI*E(k)****************/ 
if(PID->EkFlag_Uint8[1]==0)      
  PostSum += Temp[1];                                 //������
else
   ;                                                 //�ղ�����E(K)>0
/****KD*[E(k-2)+E(k)-2E(k-1)]****/                           
if(PID->EkFlag_Uint8[2]==0)
PostSum += Temp[2];                               //������
else
  NegSum += Temp[2];                             //������
/***************U(K)***************/                             
PostSum += (uint32)PID->Uk_Uint16;    
        
if(PostSum > NegSum )                         // �Ƿ������Ϊ����
{ Temp[0] = PostSum - NegSum;
if( Temp[0] < MAXOUT )                         //С�����޷�ֵ��Ϊ����ֵ���
PID->Uk_Uint16 = (uint16)Temp[0];
else
  PID->Uk_Uint16 = MAXOUT;                     //����Ϊ���޷�ֵ���
}
else                                     //���������Ϊ�����������0(���޷�ֵ���)
   PID->Uk_Uint16 = 0;
}
}
else 
{ PID->Uk_Uint16 = 0;  }

}


