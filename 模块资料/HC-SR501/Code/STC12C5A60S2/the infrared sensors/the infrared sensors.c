#include<reg51.h>
sbit HCR501 =P2^0;
sbit LED =P1^0;
void delay500ms(void) 
{
	unsigned char a,b,c;
	for(c=23;c>0;c--){
		for(b=152;b>0;b--){
			for(a=70;a>0;a--){}
		}
	}
}
int main(void)
{
	while(1)
	{
	delay500ms();
	if(HCR501 ==1)
	{
		LED=0;
	}
	else
	LED=1;
	}	
	return 0;
}












