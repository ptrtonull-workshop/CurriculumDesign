#include<reg52.h>								
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int
///////////////////////////////////////////////////////
unsigned char car_num=0;	//��λ��ֵ					 
unsigned char Set_car_H=4;  //���ó�����ֵ
signed char   s_car_num=0;	//ʣ�೵λ��ֵ	

               
uchar caiji=0;    //ģʽ
void Shumaguan(uint num);
#include "shumaguan.h"
#include "NRF24l01.h"

void delay_ms(uint z)
{
	uint a,b;
	for(a=z;z>0;z--)
	for(b=110;b>0;b--);	
}   
 void main()
{		  
		  init_NRF24L01(); //��ʼ������
			TIM2Inital();
		 	while(1)
			{ 	
		   if(caiji==0){			 //�ɼ�����
				 nRF24L01_RxPacket(TxBuf);  //ʹ��������֮�� ������ɨ��Ľ����������1sһ�� //���ջ���
				  if(TxBuf[0]==1){			   
					     car_num=TxBuf[1]*10+ TxBuf[2] ;	  //��ǰ��λ
					     s_car_num=TxBuf[3]*10+ TxBuf[4] ;  //ʣ�೵λ
			       }	
			      else{	   		  
					   TxBuf[0]=0;		  //����
					   car_num=0;
					   s_car_num=0;
			       }
		      }
				  jisuan(Set_car_H,s_car_num);
       }
 }