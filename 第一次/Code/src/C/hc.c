#include <reg52.h>
#include "hc.h"
#include "beep.h"
#include "led.h"
#define uint unsigned int
sbit DQ=P2^2;
 
void delayus(uint xms)
{
   uint i,j;
   for(i=xms;i>0;i--)
   for(j=118;j>0;j--);
}
unsigned int HC()
{
	unsigned int flag;
	flag=0;
   if(DQ==1)
	{
		flag=1;
	}
	return flag;
}