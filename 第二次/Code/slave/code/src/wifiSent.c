#include <reg52.h>
#include <fire.h>
#include <gas.h>
#include <wifiSent.h>
#include <ctype.h>
#include "delay.h"
#include "hc.h"
#define uchar unsigned char
#define uint unsigned int
	


void Tranfer1(uchar *s)
{
   while(*s!='\0')
   {
     SBUF= toascii(*s);
	 while(!TI);
	 TI=0;
     s++;
	 Delay2(1);
   }
}						 

void client_init(void)
{
	Delay2(1000);
	Tranfer1("AT+CWMODE=1\r\n");
	Delay2(1000);
	Tranfer1("AT+RST\r\n");
	Delay2(2000);
	Tranfer1("AT+CWJAP=\"PtrtoNull\",\"a1234567\"\r\n");
	Delay2(10000);
	Tranfer1("AT+CIPSTART=\"TCP\",\"192.168.4.1\",5000\r\n");
	Delay2(3000);
}

void send_message(void)
{
	Tranfer1("AT+CIPSEND=4");
	Delay2(1000);
}
