/************************************************************
����˵����
���������к����gprsģ���ҵ��������źſ�ʵ�ֽӴ�绰���Ͷ��ŵȹ���


*************************************************************/
#include <REG51.H>
#include <string.H>
#define uchar unsigned char
#define uint unsigned int
//�����ǰ�����LED�����ã���Px_x�ĳ��Լ���Ӧ�Ľš�
//���������51��Ƭ���ľ����С

sbit P10=P1^0;
sbit P11=P1^1;
sbit P12=P1^2;
sbit P13=P1^3;
sbit P14=P1^4;
sbit P15=P1^5;

#define FOSC_110592M
//#define FOSC_12M
//�����ǿ����󲦴���ֻ��ţ��ĳ��Լ���Ҫ��ĺ��뼴�ɡ�
uchar num[] = "ATD10086;\r\n";
//������GSMģ�鷵������
uchar rec_data[50];
uchar rec_num;
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

/*����ͨѶ�жϣ��շ���ɽ�������ж�*///�磺+CMTI:"SM",2
void Serial_interrupt() interrupt 4 
{

	uchar temp;
	temp=SBUF;
	rec_data[rec_num++]=temp;
	if(rec_num>=50)
		rec_num=0;
	else
		;
	RI=0;//�����ж��ź����㣬��ʾ����������

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
void Uart1BYTE(uchar temp)
{
		SBUF=temp;
		while(!TI);//�ȴ���������źţ�TI=1������
		TI=0;

}

uchar hand(uchar *ptr)
{
	if(strstr(rec_data,ptr)!=NULL)
		return 1;
	else
		return 0;
}

void clear_rec_data()
{
	uchar i;
	for(i=0;i<strlen(rec_data);i++)
	{
		rec_data[i]='0';
	
	}
	rec_num=0;


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

	//Uart1Sends(num);
	//�����ڵ�Ƭ������GSMģ��ǰ���������� AT ָ�����ͬ��ģ���뵥Ƭ���Ĳ�����
	Uart1Sends("ATI\r\n"); //����
	while(!hand("OK")) 
	{
		clear_rec_data();
		i++;
		Uart1Sends("ATI\r\n");//
		DelaySec(1);//��ʱ
		if(i>=5)
		{
			break;
			//return;
		}
		else
			;
	}
	P10=0;
	clear_rec_data();//ɾ���洢��GSMģ�鷵�ص����ݣ��Ա����Ժ�����ж�
	DelaySec(1);//��ʱ
	Uart1Sends("AT+CSQ\r\n");//�ź�����
	DelaySec(1);//��ʱ
	i=0;
	while(!hand("OK")) //������ָ��GSMģ���Ƿ�ִ��OK
	{
		clear_rec_data();
		i++;
		Uart1Sends("AT+CSQ\r\n");//
		DelaySec(1);//��ʱ
		if(i>=5)
		{
			break;
			//return;
		}
		else
			;
	}
	P11=0;
	clear_rec_data();
	DelaySec(1);//��ʱ
	Uart1Sends("AT+CPIN?\r\n");//�鿴�Ƿ�����ֻ���
	DelaySec(1);//��ʱ
	i=0;
	while(!hand("READY")) //���SIMģ���Ƿ��յ�SIM��READY
	{
		clear_rec_data();
		i++;
		Uart1Sends("AT+CPIN?\r\n");//�Ƿ�ע�ᵽ����
		DelaySec(1);//��ʱ
		if(i>=5)
		{
			break;
			//return;
		}
		else
			;		
	}
	P12=0;
	Uart1Sends("AT+COPS?\r\n");//�Ƿ�ע�ᵽ����
	DelaySec(1);//��ʱ
	i=0;
	while(!hand("CHINA")) //����Ƿ��յ�ģ�鷵�ص�CHINA
	{
		clear_rec_data();
		i++;
		Uart1Sends("AT+COPS?\r\n");//�Ƿ�ע�ᵽ����
		DelaySec(1);//��ʱ
		if(i>=5)
		{
			break;
			//return;
		}
		else
			;		
	}
	P13=0;
	clear_rec_data();
	DelaySec(1);//��ʱ
//�����Ƿ���Ӣ�Ķ��Ŷ���
	Uart1Sends("AT+CMMI=2,1\r\n"); //������
	DelaySec(1);//��ʱ
	Uart1Sends("AT+CMGF=1\r\n");  //��ʽ1
	DelaySec(1);//��ʱ
	Uart1Sends("AT+CMGS=\"10086\"\r\n");  //�˴��޸Ķ��Ž��շ��绰��
	DelaySec(1);//��ʱ
	Uart1Sends("ye");  //�˴��޸Ķ�������
	DelaySec(1);//��ʱ
	Uart1BYTE(0X1A);
	DelaySec(1);//��ʱ
	DelaySec(1);//��ʱ
	DelaySec(1);//��ʱ
	DelaySec(1);//��ʱ
	P14=0;
//����Ӣ�Ķ��Ž���
	Uart1Sends("AT+CMGD=1\r\n");//ɾ��SIM���е�����
	DelaySec(1);//��ʱ
	//�����ǲ���10086����
	Uart1Sends(num);  //����10086
	DelaySec(1);//��ʱ
	DelaySec(1);//��ʱ
	DelaySec(1);//��ʱ
	DelaySec(1);//��ʱ
	//����绰�������
	//��������û��ʵ�ʲ��ԣ������ο�
	while(1)
	{
		if(hand("CMTI"))
		{
			P13=0;
			clear_rec_data();
			DelaySec(1);//��ʱ
			Uart1Sends("AT+CMGR=1\r\n");//
			DelaySec(1);//��ʱ
			i=0;
			while(!hand("OK")) 
			{
				clear_rec_data();
				i++;
				Uart1Sends("AT+CMGR=1\r\n");//
				DelaySec(1);//��ʱ
				if(i>=2)   //chucuo
				{
					break;
					//return;
				}
				else
					;		
			}
			clear_rec_data();
			DelaySec(1);//��ʱ
			if(hand("relay on"))
			{
				P14=0;
				//break;
			}
			else if(hand("relay off"))
			{
				
				P15=0;
				//break;
			}
			else
			{
				//break;
			}
			Uart1Sends("AT+CMGD=1\r\n");//
			DelaySec(1);//��ʱ

		
		}
		else if(hand("ring")) //�绰���� �Ҷϵ绰
		{
			
			Uart1Sends("ATH\r\n");//
			DelaySec(1);//��ʱ
			i=0;
			while(!hand("OK")) 
			{
				clear_rec_data();
				i++;
				Uart1Sends("ATH\r\n");//
				DelaySec(1);//��ʱ
				if(i>=2)
				{
					break;
					//return;
				}
				else
					;		
			}
			clear_rec_data();
			DelaySec(1);//��ʱ		
	
		}
		else
		{
			;
		}
	}
}