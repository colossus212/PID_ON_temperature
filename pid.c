#include"defines.h"
#include"PID.h"
const unsigned int MAXOUT=200;
//================================================================
// PID->H
// Operation about PID algorithm procedure 
// C51编译器  Keil 7.08
//================================================================
// 作者:zhoufeng
// Date :2007-08-06
// All rights reserved.
//================================================================

uint8        out ;                 // 加热输出
uint8        count;               // 输出时间单位计数器
/*********************************
PID = Uk + KP*[E(k)-E(k-1)]+KI*E(k)+KD*[E(k)-2E(k-1)+E(k-2)];(增量型PID算式)
函数入口: RK(设定值),CK(实际值),KP,KI,KD
函数出口: U(K)
//PID运算函数
********************************/
void     PIDOperation (PIDValueStr *PID)  
{ 
uint32       Temp[3];                                        //中间临时变量
uint32       PostSum;                                       //正数和
uint32       NegSum;                                       //负数和
Temp[0] = 0;
Temp[1] = 0;
Temp[2] = 0;
PostSum = 0;
NegSum  = 0;
if( PID->RK_Uint16 > PID->CK_Uint16 )                    //设定值大于实际值否？
{
  if( PID->RK_Uint16 - PID->CK_Uint16 >100 )            //偏差大于10否？
  {
   PID->Uk_Uint16 = MAXOUT;    }                        //偏差大于10为上限幅值输出(全速加热)
  else
  {
   Temp[0] = PID->RK_Uint16 - PID->CK_Uint16;       //偏差<=10,计算E(k)
   PID->EkFlag_Uint8[1]=0;                        //E(k)为正数
   //数值移位
      PID->Ek_Uint32[2] = PID->Ek_Uint32[1];
      PID->Ek_Uint32[1] = PID->Ek_Uint32[0];
      PID->Ek_Uint32[0] = Temp[0];
/****************************************/
      if( PID->Ek_Uint32[0] >PID->Ek_Uint32[1] )                            //E(k)>E(k-1)否？
      {
  Temp[0]=PID->Ek_Uint32[0] - PID->Ek_Uint32[1];           //E(k)>E(k-1)
        PID->EkFlag_Uint8[0]=0;  }                                       //E(k)-E(k-1)为正数
   else
{
  Temp[0]=PID->Ek_Uint32[0] - PID->Ek_Uint32[1];        //E(k)<E(k-1)
        PID->EkFlag_Uint8[0]=1;  }                                               //E(k)-E(k-1)为负数
/****************************************/
      Temp[2]=PID->Ek_Uint32[1]*2 ;                                             // 2E(k-1)
if( (PID->Ek_Uint32[0]+ PID->Ek_Uint32[2])>Temp[2] )            //E(k-2)+E(k)>2E(k-1)否？
      {
  Temp[2]=(PID->Ek_Uint32[0]+ PID->Ek_Uint32[2])-Temp[2];     //E(k-2)+E(k)>2E(k-1)
        PID->EkFlag_Uint8[2]=0;  }                                          //E(k-2)+E(k)-2E(k-1)为正数
   else
{
  Temp[2]=Temp[2]-(PID->Ek_Uint32[0]+ PID->Ek_Uint32[2]);  //E(k-2)+E(k)<2E(k-1)
        PID->EkFlag_Uint8[2]=1;  }                                       //E(k-2)+E(k)-2E(k-1)为负数
/****************************************/       
      Temp[0] = (uint32)PID->KP_Uint8 * Temp[0];                        // KP*[E(k)-E(k-1)]
      Temp[1] = (uint32)PID->KI_Uint8 * PID->Ek_Uint32[0];              // KI*E(k)
      Temp[2] = (uint32)PID->KD_Uint8 * Temp[2];                      // KD*[E(k-2)+E(k)-2E(k-1)]

/*以下部分代码是讲所有的正数项叠加，负数项叠加*/     
/**********KP*[E(k)-E(k-1)]**********/
if(PID->EkFlag_Uint8[0]==0)
  PostSum += Temp[0];                                    //正数和
else                                              
  NegSum += Temp[0];                                    //负数和
/********* KI*E(k)****************/ 
if(PID->EkFlag_Uint8[1]==0)      
  PostSum += Temp[1];                                 //正数和
else
   ;                                                 //空操作，E(K)>0
/****KD*[E(k-2)+E(k)-2E(k-1)]****/                           
if(PID->EkFlag_Uint8[2]==0)
PostSum += Temp[2];                               //正数和
else
  NegSum += Temp[2];                             //负数和
/***************U(K)***************/                             
PostSum += (uint32)PID->Uk_Uint16;    
        
if(PostSum > NegSum )                         // 是否控制量为正数
{ Temp[0] = PostSum - NegSum;
if( Temp[0] < MAXOUT )                         //小于上限幅值则为计算值输出
PID->Uk_Uint16 = (uint16)Temp[0];
else
  PID->Uk_Uint16 = MAXOUT;                     //否则为上限幅值输出
}
else                                     //控制量输出为负数，则输出0(下限幅值输出)
   PID->Uk_Uint16 = 0;
}
}
else 
{ PID->Uk_Uint16 = 0;  }

}


