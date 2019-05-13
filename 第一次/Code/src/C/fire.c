/******************************************
传感器触发测试
单片机：STC89C52
波特率：9600
*****************************************/
#include <reg52.h>
#include <fire.h>
unsigned char date;
#define uchar unsigned char
#define uint unsigned int
sbit key1=P2^0;
/*
********************************************************************************
** 函数名称 ： delay(uint z)
** 函数功能 ： 延时函数
********************************************************************************
*/
void Fdelay(uint z)
{																							   
    uint i,j;
    for(i=z;i>0;i--)
        for(j=110;j>0;j--);
} 


//*****串口初始化函数***********

//******************************
void Initial_com(void)
{
	 EA=1;        //开总中断
	 ES=1;        //允许串口中断
	 ET1=1;        //允许定时器T1的中断
	 TMOD=0x20;   //定时器T1，在方式2中断产生波特率
	 PCON=0x00;   //SMOD=0
	 SCON=0x50;   // 方式1 由定时器控制
	 TH1=0xfd;    //波特率设置为9600
	 TL1=0xfd;
	 TR1=1;       //开定时器T1运行控制位
}

//*************************
//**********主函数*********
//*************************
unsigned int fire()
{
	unsigned int data1;
	data1=0;
	if(key1==0)
	{
		data1=1;
	}
	/*
	 	 if(key1==0)
		{
			Fdelay(2);	  //消抖动
			if(key1==0)	  //确认触发
			{
				 SBUF=0X01;
				 Fdelay(200);
			}
		}
		 if(RI)
		{
			date=SBUF;    //单片机接受
			SBUF=date;    //单片机发送
			RI=0;
		 }
	*/
	  return data1;
}