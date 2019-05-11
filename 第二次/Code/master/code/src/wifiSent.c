#include <reg52.h>
#include <fire.h>
#include <gas.h>
#include <wifiSent.h>
unsigned char date;
#define uchar unsigned char
#define uint unsigned int
	
void UART_init()
{
  SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ1
	TH1=0XFD;		    //��������ʼֵ���ã�ע�Ⲩ������9600
	TL1=0XFD;	
	TR1=1;						    //�򿪼�����
}

/* ����wifi */
void set_wifi(void)
{
  Delay2(1000);
	Tranfer("AT+CWMODE=1\r\n");
	Delay2(1000);	
  Tranfer("AT+RST\r\n");	
	Delay2(1000);
	Tranfer("AT+CIPMUX=0\r\n");	 //������
	Delay2(1000);	
  Tranfer("AT+CWJAP=\"ESP8266\",\"123456789\"\r\n");
	Delay2(5000);
	Tranfer("AT+CIPSTART=\"TCP\",\"192.168.4.1\",5000\r\n");
	Delay2(2000);
}
void Sent(uint gasValue,uint hcValue)
{
	Tranfer("AT+CIPSEND=10\r\n");	  
	Tranfer("R5");
	SBUF=gasValue;Delay2(1);
	SBUF=hcValue;Delay2(1);
}

void SentValue()
{
	UART_init();
	Sent(Gas(),HC());
}

