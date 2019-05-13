#include "reg52.h"
#include "string.h"
#define uchar unsigned char
#define uint unsigned int

//�����ǰ�����LED�����ã���Px_x�ĳ��Լ���Ӧ�Ľš�

#define LED1_ON P3_2 = 1
#define LED1_OFF P3_2 = 0
#define LED2_ON P3_3 = 1
#define LED2_OFF P3_3 = 0
#define LED3_ON P3_4 = 1
#define LED3_OFF P3_4 = 0
#define LED4_ON P3_5 = 1
#define LED4_OFF P3_5 = 0
//���������51��Ƭ���ľ����С��ʹ��
#define FOSC_110592M
//#define FOSC_12M
//�����ǿ����󲦴���ֻ��ţ��ĳ��Լ���Ҫ��ĺ��뼴�ɡ�
uchar NUM[] = "15296811438";
uchar GsmRcv[50] = {0}
uchar GsmRcvAt[50] = {0};
uchar GsmRcvCnt = 0;
uchar GsmAtFlag = 0;
//�����޸Ķ�Ӧ���ֻ��������̣��й��ƶ������й���ͨ��������й���ͨ���Ͱѵ�һ��ע�͵����򿪵ڶ�����
uchar SER[] = "CHINA MOBILE";
//uchar SER[] = "CHINA UNICOM";
void SerialInti()//��ʼ�����򣨱���ʹ�ã������޷��շ���
{
		TMOD=0x20;//��ʱ��1����ģʽ2:8λ�Զ����ض�ʱ��
		#ifdef FOSC_12M //��������ݾ����С���ò�ͬ����ֵ��ʼ������
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

//ע�⣬���۽��յ��źŻ��Ƿ������źţ�������жϷ�������

void Serial_interrupt() interrupt 4
{
	uchar i = 0;
	if(RI == 1) //�յ���Ϣ
	{
		RI=0;//�����ж��ź����㣬��ʾ����������
		GsmRcv[GsmRcvCnt] = SBUF;
		// Uart1Send(tmp);
		GsmRcvCnt++;
		//�յ���������ATָ�������ATָ������0x0a 0x0d��β�ġ��������жϣ��ڽ��յĹ������Ƿ��յ�0x0a 0x0d
		if(GsmRcv[GsmRcvCnt-2] == 0x0d && GsmRcv[GsmRcvCnt-1] == 0x0a && GsmRcvCnt >= 2)
		{
			//һ���յ�0x0a 0x0d���ͽ����ݱ����������û����������жϡ�
			for(i=0; i<>
			{
				GsmRcvAt[i] = GsmRcv[i];
				GsmRcv[i] = 0;
			}
				GsmRcvCnt = 0;
				GsmAtFlag = 1;//�յ���������atָ�ͨ�������־λ��1��������������֪��ȥ�ж��ˡ�
			}
			else if(GsmRcvCnt >= 50)//��Ϊ�ڴ����ޣ��յ���50���ַ�����û�п���0x0a 0x0d�Ļ��������¿�ʼ���հɡ�
			{
				GsmRcvCnt = 0;
			}
		}
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
//��ʱ���������1s�ӣ�������ʱ��Ļ���׼...
void DelaySec(int sec)
{
	uint i , j= 0;
	for(i=0; i<>
	{
		for(j=0; j<65535; j++)
		{
			
		}
	}
}
void main()
{
	uint i,j = 0;
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	SerialInti();
	P2_4 = 0;
	//�ж��Ƿ��������
	GsmAtFlag = 0;
	while(GsmAtFlag == 0)
	{
		Uart1Sends("ati\r");//����sim300������
		LED1_ON;
		DelaySec(1);//��ʱ1��
		LED1_OFF;
	}
	GsmAtFlag = 0;
	LED1_OFF;
	//����ź�
	while(1)
	{
		Uart1Sends("AT+COPS?\r");
		LED2_ON;
		DelaySec(1);//��ʱ1��
		LED2_OFF;
		while(GsmAtFlag == 0);
		if(strstr(GsmRcvAt, SER) )//����Ƿ��յ� CHINA MOBILE ��������Ϣ������յ�֤����������������
		{
			break;
		}
	}
	LED2_OFF;
	//������ʾ
	while(1)
	{
		//��������磬ģ�鷵��RING����ʱ����AT+CLCC/rȥ��ȡ�������
		if(strstr(GsmRcvAt, "RING"))
		{
			Uart1Sends("AT+CLCC\r");//����AT+CLCC/rȥ��ȡ�������
		}
		if(strstr(GsmRcvAt, "+CLCC") && strstr(GsmRcvAt, NUM) )//����Ƿ��յ�������ʾ�Ͷ�Ӧ��������롣
		{
			LED2_ON;
		}
		if(strstr(GsmRcvAt, "NO CARRIER"))//���Է��Ƿ�Ҷϵ绰�����ָ���ȴ��Է��Ҷ��˵绰�����ִ�С�
		{
			LED2_OFF;
		}
		//һ����ʱ����LED��˸���Թ۲�ϵͳ�����Ƿ�������
		i++;
		if(i <= 500)
		{
			LED1_ON;
		}
		else if(i > 500 && i < 1000)
		{
			LED1_OFF;
		}
		else
		{
			i = 0;
		}
	}
}
