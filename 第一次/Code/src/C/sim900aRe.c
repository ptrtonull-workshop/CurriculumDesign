#include "reg52.h"
#include "string.h"
#define uchar unsigned char
#define uint unsigned int

//以下是板子上LED的配置，把Px_x改成自己对应的脚。

#define LED1_ON P3_2 = 1
#define LED1_OFF P3_2 = 0
#define LED2_ON P3_3 = 1
#define LED2_OFF P3_3 = 0
#define LED3_ON P3_4 = 1
#define LED3_OFF P3_4 = 0
#define LED4_ON P3_5 = 1
#define LED4_OFF P3_5 = 0
//以下是你的51单片机的晶振大小，使用
#define FOSC_110592M
//#define FOSC_12M
//以下是开机后拨打的手机号，改成自己想要打的号码即可。
uchar NUM[] = "15296811438";
uchar GsmRcv[50] = {0}
uchar GsmRcvAt[50] = {0};
uchar GsmRcvCnt = 0;
uchar GsmAtFlag = 0;
//以下修改对应的手机卡服务商，中国移动或者中国联通。如果是中国联通，就把第一个注释掉。打开第二个。
uchar SER[] = "CHINA MOBILE";
//uchar SER[] = "CHINA UNICOM";
void SerialInti()//初始化程序（必须使用，否则无法收发）
{
		TMOD=0x20;//定时器1操作模式2:8位自动重载定时器
		#ifdef FOSC_12M //在这里根据晶振大小设置不同的数值初始化串口
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

//注意，无论接收到信号还是发送完信号，都会进中断服务程序的

void Serial_interrupt() interrupt 4
{
	uchar i = 0;
	if(RI == 1) //收到信息
	{
		RI=0;//接收中断信号清零，表示将继续接收
		GsmRcv[GsmRcvCnt] = SBUF;
		// Uart1Send(tmp);
		GsmRcvCnt++;
		//收到了完整的AT指令，完整的AT指令是以0x0a 0x0d结尾的。故作此判断，在接收的过程中是否收到0x0a 0x0d
		if(GsmRcv[GsmRcvCnt-2] == 0x0d && GsmRcv[GsmRcvCnt-1] == 0x0a && GsmRcvCnt >= 2)
		{
			//一旦收到0x0a 0x0d，就将数据保存起来。用户主函数的判断。
			for(i=0; i<>
			{
				GsmRcvAt[i] = GsmRcv[i];
				GsmRcv[i] = 0;
			}
				GsmRcvCnt = 0;
				GsmAtFlag = 1;//收到了完整的at指令，通过这个标志位置1，这样主函数就知道去判断了。
			}
			else if(GsmRcvCnt >= 50)//因为内存有限，收到了50个字符还是没有看到0x0a 0x0d的话，就重新开始接收吧。
			{
				GsmRcvCnt = 0;
			}
		}
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
	for(i=0; i<>
	{
		for(j=0; j<65535; j++)
		{
			
		}
	}
}
void main()
{
	uint i,j = 0;
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	SerialInti();
	P2_4 = 0;
	//判断是否启动完成
	GsmAtFlag = 0;
	while(GsmAtFlag == 0)
	{
		Uart1Sends("ati\r");//设置sim300波特率
		LED1_ON;
		DelaySec(1);//延时1秒
		LED1_OFF;
	}
	GsmAtFlag = 0;
	LED1_OFF;
	//检测信号
	while(1)
	{
		Uart1Sends("AT+COPS?\r");
		LED2_ON;
		DelaySec(1);//延时1秒
		LED2_OFF;
		while(GsmAtFlag == 0);
		if(strstr(GsmRcvAt, SER) )//检测是否收到 CHINA MOBILE 服务商信息。如果收到证明是连接上网络了
		{
			break;
		}
	}
	LED2_OFF;
	//来电提示
	while(1)
	{
		//如果有来电，模块返回RING，此时发送AT+CLCC/r去读取来电号码
		if(strstr(GsmRcvAt, "RING"))
		{
			Uart1Sends("AT+CLCC\r");//发送AT+CLCC/r去读取来电号码
		}
		if(strstr(GsmRcvAt, "+CLCC") && strstr(GsmRcvAt, NUM) )//检测是否收到来电显示和对应的来电号码。
		{
			LED2_ON;
		}
		if(strstr(GsmRcvAt, "NO CARRIER"))//检测对方是否挂断电话。这个指令会等待对方挂断了电话数秒后执行。
		{
			LED2_OFF;
		}
		//一定的时间让LED闪烁，以观察系统运行是否正常。
		i++;
		if(i <= 500)
		{
			LED1_ON;
		}
		else if(i > 500 && i < 1000)
		{
			LED1_OFF;
		}
		else
		{
			i = 0;
		}
	}
}
