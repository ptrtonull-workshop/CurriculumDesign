/*
	
*/
#include <REG51.H>
#include "beep.h"
#include "hc.h"
#include "led.h"
#include "fire.h"
#include "wifiReceive.h"
#include "wifiSent.h"

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
		SentValue();
	}
}

