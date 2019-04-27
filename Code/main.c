/************************************************************
����˵����
���������к����gprsģ���ҵ��������źţ��Ͳ���ָ���绰��
1.���Լ���51��Ƭ���Ĵ���1���ӵ�GSM 232��
2.�ҵ�������ǰ���#define��������˵���޸ĺ��Լ��ĵ�Ƭ�����ã��������
2.���س���
3.�ȴ����ͳɹ�
*************************************************************/
#include <REG51.H>
#include "beep.h"
#include "hc.h"
#include "led.h"
#include "fire.h"

#define uchar unsigned char
#define uint unsigned int
//�����ǰ�����LED�����ã���Px_x�ĳ��Լ���Ӧ�Ľš�
//���������51��Ƭ���ľ����С
#define FOSC_110592M
//#define FOSC_12M

//�����ǿ������͵��ֻ������ݣ����͵ĺ����ڳ������޸ġ�
uchar sms_text[] = "abc123";
  
//ע�⣬���۽��յ��źŻ��Ƿ������źţ�������жϷ�������
/*��ʼ�����򣨱���ʹ�ã������޷��շ������γ��򽫻�ʹ�ö�ʱ��1*/

extern void beep();

void SerialInti()//��ʼ�����򣨱���ʹ�ã������޷��շ���
{
	TMOD=0x20;//��ʱ��1����ģʽ2:8λ�Զ����ض�ʱ��
#ifdef FOSC_12M		   //��������ݾ����С���ò�ͬ����ֵ��ʼ������
	TH1=0xf3;//װ���ֵ��������2400
	TL1=0xf3;	
#else 	
	TH1=0xfd;//װ���ֵ��������9600
	TL1=0xfd;
#endif //end of SOC_12M
	TR1=1;//�򿪶�ʱ��
	SM0=0;//���ô���ͨѶ����ģʽ����10Ϊһ�����ͣ������ʿɱ䣬�ɶ�ʱ��1������ʿ��ƣ�
	SM1=1;//(ͬ��)�ڴ�ģʽ�£���ʱ�����һ�ξͷ���һ��λ������
	REN=1;//���н�������λ��Ҫ������sm0sm1�ٿ���������
	EA=1;//�����ж�
	ES=1;//�����п��ж�	
}

void DelaySec(int sec)
{
	uint i, j= 0;
	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}

/*����ͨѶ�жϣ��շ���ɽ�������ж�*/
void Serial_interrupt() interrupt 4 
{
//	a=SBUF;
	P2=SBUF;
	RI=0;//�����ж��ź����㣬��ʾ����������
//	flag=1;//�����жϵı�־����
}

void Uart1Send(uchar c)
{
	SBUF=c;
	while(!TI);//�ȴ���������źţ�TI=1������
	TI=0;	
}

//���п���������char�����飬������ֹ��/0��ֹͣ
void Uart1Sends(uchar *str)
{
	while(*str!='\0')
	{
		SBUF=*str;
		while(!TI);//�ȴ���������źţ�TI=1������
		TI=0;
		str++;
	}
}

void sendMs(){
		Uart1Sends("AT+CSCS=\"GSM\"\r\n");
		DelaySec(3);//��ʱ3��
		Uart1Sends("AT+CMGF=1\r\n");
		DelaySec(3);//��ʱ3��
		Uart1Sends("AT+CMGS=\"13104610925\"\r\n");//�˴��޸�Ϊ�Է��ĵ绰��
		DelaySec(5);//��ʱ3��
		Uart1Sends(sms_text);//�޸Ķ�������
		Uart1Send(0x1a);
		DelaySec(15);//��ʱ20��
}
void main()
{
	uchar i= 0;
	SerialInti();
	Initial_com();
	//Led();
	while(1){
		if(fire()==0X01)
	{
		Led();
	}
	}
	
}
