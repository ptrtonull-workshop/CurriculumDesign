#include "reg52.h"

typedef unsigned int u16;	  
typedef unsigned char u8;

sbit led=P2^0;		 
void Ldelay(u16 i)
{
	while(i--);	
}
void Led()
{
	led=0;
	Ldelay(50000); 
}
void LedC()
{
	led=1;
	Ldelay(50000); 
}

