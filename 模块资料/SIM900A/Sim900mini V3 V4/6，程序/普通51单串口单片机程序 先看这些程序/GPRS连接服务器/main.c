/************************************************************
����˵����
���������к����gprsģ���ҵ��������źţ��ͻ�����ָ���ķ�������
1.���Լ���51��Ƭ���Ĵ���1���ӵ�GSM��232�ӿ�
2.�ҵ�������ǰ���#define��������˵���޸ĺ��Լ��ĵ�Ƭ������.
3.ʹ�����������ҳhttp://www.ip138.com/����ѯ�Լ�������ip��ַ��
4.�ڹ������ҵ� ���Թ���\socket tool.exe �򿪣�Э�����ͣ�tcp��������ip��ַ���ض˿�Ĭ�ϡ����������
5.���س���
6.����ģ��,�ȴ��źŵ���˸���������ģ����ֻ����������������������յ�ģ�鷢������Ϣ

*************************************************************/
#include <REG51.H>
#include <string.h>

#define uchar unsigned char
#define uint unsigned int

//���������51��Ƭ���ľ����С
#define FOSC_110592M
//#define FOSC_12M


//�������ڱ��浥Ƭ���յ�ģ�鷢����ATָ�ͨ����Щָ�Ƭ�������ж�ģ���״̬
uchar GsmRcv[50] = {0};
uchar GsmRcvAt[50] = {0}; 
uchar GsmRcvCnt = 0;
uchar GsmAtFlag = 0;
   
//ע�⣬���۽��յ��źŻ��Ƿ������źţ�������жϷ�������
/*��ʼ�����򣨱���ʹ�ã������޷��շ������γ��򽫻�ʹ�ö�ʱ��1*/
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

/*����ͨѶ�жϣ��շ���ɽ�������ж�*/
void Serial_interrupt() interrupt 4 
{
	uchar i = 0;

	if(RI == 1)	//�յ���Ϣ
	{

		RI=0;//�����ж��ź����㣬��ʾ����������
		
		GsmRcv[GsmRcvCnt] = SBUF;
//		Uart1Send(tmp);
		GsmRcvCnt++;
		//�յ���������ATָ�������ATָ������0x0a 0x0d��β�ġ��������жϣ��ڽ��յĹ������Ƿ��յ�0x0a 0x0d
		if(GsmRcv[GsmRcvCnt-2] == 0x0d && GsmRcv[GsmRcvCnt-1] == 0x0a && GsmRcvCnt >= 2)
		{
			//һ���յ�0x0a 0x0d���ͽ����ݱ����������û����������жϡ�			
			for(i=0; i<GsmRcvCnt; i++)
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

//��ʱ���������1s�ӣ�������ʱ��Ļ���׼...
void DelaySec(int sec)
{
	uint i , j= 0;

	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}



void main()
{
	uchar i = 0;
	SerialInti();

//�ж��Ƿ��������
	GsmAtFlag = 0;
	while(GsmAtFlag == 0)
	{
		Uart1Sends("ATI\r\n");//����sim300������
		DelaySec(1);//��ʱ1��
	}
	GsmAtFlag = 0;

//����ź�
	while(1)
	{
		Uart1Sends("AT+COPS?\r\n");
		DelaySec(2);//��ʱ1��
		while(GsmAtFlag == 0);
		if(strstr(GsmRcvAt, "CHINA") )//����Ƿ��յ� CHINA MOBILE ��������Ϣ������յ�֤����������������
		{
			break;
		}		
	}

	while(1)
	{
		Uart1Sends("AT+CIPCLOSE\r\n");
		DelaySec(1);
		Uart1Sends("AT+CIPSHUT\r\n");	
		DelaySec(1);
		Uart1Sends("AT+CLPORT=\"TCP\",\"2022\"\r\n");//����ָ��ָ�����ض˿�
		DelaySec(1);
		Uart1Sends("AT+CIPSTART=\"TCP\",\"110.212.216.243\",\"8080\"\r\n");//�˴��޸��㽨����������IP���������˿ں�8080
		DelaySec(1);
		if(GsmAtFlag == 1 && strstr(GsmRcvAt, "CONNECT OK") )//����Ƿ��յ� CONNECT OK ,��������ӳɹ�
		{
			Uart1Sends("AT+CIPSEND\r\n");
			DelaySec(1);
			DelaySec(1);
			Uart1Sends("abc123");//���������������
	        DelaySec(1);
			Uart1Send(0x1a);//��0x1a����
		
			DelaySec(15);//��ʱ20��	
			break;
		}			
	
	}


}
