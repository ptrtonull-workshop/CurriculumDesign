/*
	
*/
#include <REG51.H>
#include "beep.h"
#include "hc.h"
#include "led.h"
#include "fire.h"

//extern void beep();
void init()
{
	SerialInti();
	Initial_com();
}
void main()
{
	//uchar i= 0;
	init();
	while(1)
	{
		if(fire()==0X01)
		{
			Led();
		}
	}
}
