#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

int main(void)
{
	void init(void);
}
	
void ms_delay(uint t)

  {
  uint i,j;
  for(i=t;i>=0;i--)
  for(j=110;j>=0;j--);
  }
	
void us_delay(uchar t)
  {
  while(t--);
  }

	
	void Send_Uart(uchar value)
  {
  ES=0; 
  TI=0; 
  SBUF=value; 
  while(TI==0);  
	TI=0; 
  ES=1; 
  }
	
void Tranfer(uchar *puf)
{
	while(*puf!='\0') //????????
	{
		Send_Uart(*puf); //?WIFI?????????
		us_delay(5);
		puf++;
  }
  us_delay(5);
  Send_Uart('\r');//??
  us_delay(5);
  Send_Uart('\n'); //??
  ms_delay(1000);
}	

	
	
void init(void)
{	

	Delay2(1000);
	Tranfer("AT+CWMODE=1\r\n");
	Delay2(1000);
	Tranfer("AT+RST\r\n");
	Delay2(1000);
	Tranfer("AT+CWJAP=\"PtntoNull\",\"a1234567\"");
	Delay2(5000);
	Tranfer("AT+CIPSTART=\"TCP\",\"192.168.4.1\",5000\r\n");
	Delay2(5000);
	
	Tranfer("AT+CIPSEND=5");
	Delay2(1000);
		Tranfer("AT+CIPSEND=5");
	Delay2(1000);
		Tranfer("AT+CIPSEND=5");
	Delay2(1000);
		Tranfer("AT+CIPSEND=5");
	Delay2(1000);
		Tranfer("AT+CIPSEND=5");
	Delay2(1000);
		Tranfer("AT+CIPSEND=5");
	Delay2(1000);
}
