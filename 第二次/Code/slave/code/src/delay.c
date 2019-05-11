#include <reg52.h>
#include <delay.h>


void Delay2(unsigned long cnt)
{
	long i;
 	for(i=0;i<cnt*10;i++);
}