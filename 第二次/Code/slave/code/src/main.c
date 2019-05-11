#include "reg52.h"
#include "delay.h"
#include "wifiSent.h"
#define uint unsigned int
#define uchar unsigned char


	
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
  while(*puf!='\0') 
  {
	Send_Uart(*puf); 
	us_delay(5);
	puf++;
  }
  us_delay(5);
  Send_Uart('\r');
  us_delay(5);
  Send_Uart('\n'); 
  ms_delay(1000);
}	

void xinit(void)
{	
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
int main(void)
{
	xinit();
	return 0;
}
