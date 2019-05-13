#include <REG51.H>
#include "beep.h"
#include "hc.h"
#include "led.h"
#include "fire.h"
#include "sim900a.h"

#define uchar unsigned char
uchar FireMs[] = "fire!";
uchar HCMs[]= "body";
uchar NoMs[]= "no";

unsigned int a=0;
unsigned int b=0;
void init()
{
	SerialInti();
	Initial_com();
}
void main()
{
	init();
	while(1)
	{
		/*
		b=fire();
		while(b==1)
		{
			sendMs(FireMs);
			b=0;
		}
		*/
		a=HC();
		while(a==1)
		{
			sendMs(HCMs);
			a=0;
		}
	}
}