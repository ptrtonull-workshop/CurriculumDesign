/************************************************************
程序说明：
本程序运行后如果gprs模块找到服务商信号，就拨打指定电话。
1.将自己的51单片机的串口1连接到GSM 的232接口
2.找到程序中前面的#define处，根据说明修改好自己的单片机配置，编译程序
2.下载程序
3.等待接通电话


*************************************************************/
#include <REG51.H>

#define uchar unsigned char
#define uint unsigned int
//以下是板子上LED的配置，把Px_x改成自己对应的脚。


//以下是你的51单片机的晶振大小
#define FOSC_110592M
//#define FOSC_12M

//以下是开机后拨打的手机号，改成自己想要打的号码即可。
uchar num[] = "ATD15296811438;\r\n";

   
//注意，无论接收到信号还是发送完信号，都会进中断服务程序的
/*初始化程序（必须使用，否则无法收发），次程序将会使用定时器1*/
void SerialInti()//初始化程序（必须使用，否则无法收发）
{
	TMOD=0x20;//定时器1操作模式2:8位自动重载定时器

#ifdef FOSC_12M		   //在这里根据晶振大小设置不同的数值初始化串口
	TH1=0xf3;//装入初值，波特率2400
	TL1=0xf3;	
#else 	
	TH1=0xfd;//装入初值，波特率9600
	TL1=0xfd;
#endif //end of SOC_12M
	
	TR1=1;//打开定时器
	SM0=0;//设置串行通讯工作模式，（10为一部发送，波特率可变，由定时器1的溢出率控制）
	SM1=1;//(同上)在此模式下，定时器溢出一次就发送一个位的数据
	REN=1;//串行接收允许位（要先设置sm0sm1再开串行允许）
	EA=1;//开总中断
	ES=1;//开串行口中断	
}

/*串行通讯中断，收发完成将进入该中断*/
void Serial_interrupt() interrupt 4 
{
//	a=SBUF;
	P2=SBUF;
	RI=0;//接收中断信号清零，表示将继续接收
//	flag=1;//进入中断的标志符号
}

//串行口连续发送char型数组，遇到终止号/0将停止
void Uart1Sends(uchar *str)
{
	while(*str!='\0')
	{
		SBUF=*str;
		while(!TI);//等待发送完成信号（TI=1）出现
		TI=0;
		str++;
	}
}

//延时函数大概是1s钟，不过延时大的话不准...
void DelaySec(int sec)
{
	uint i , j= 0;

	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}



void main()
{
	uchar i = 0;
	SerialInti();
	while(1)
	{
		Uart1Sends(num);
		DelaySec(20);//延时20秒
		Uart1Sends("ATH\r\n");
		DelaySec(5);//延时5秒
	}


}
