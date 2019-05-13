#include<reg52.h>								
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int
///////////////////////////////////////////////////////
unsigned char car_num=0;	//车位数值					 
unsigned char Set_car_H=4;  //设置车数数值
signed char   s_car_num=0;	//剩余车位数值	

               
uchar caiji=0;    //模式
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
		  init_NRF24L01(); //初始化无线
			TIM2Inital();
		 	while(1)
			{ 	
		   if(caiji==0){			 //采集回来
				 nRF24L01_RxPacket(TxBuf);  //使用这个语句之后 主函数扫面的进程慢到大概1s一轮 //接收回来
				  if(TxBuf[0]==1){			   
					     car_num=TxBuf[1]*10+ TxBuf[2] ;	  //当前车位
					     s_car_num=TxBuf[3]*10+ TxBuf[4] ;  //剩余车位
			       }	
			      else{	   		  
					   TxBuf[0]=0;		  //清零
					   car_num=0;
					   s_car_num=0;
			       }
		      }
				  jisuan(Set_car_H,s_car_num);
       }
 }