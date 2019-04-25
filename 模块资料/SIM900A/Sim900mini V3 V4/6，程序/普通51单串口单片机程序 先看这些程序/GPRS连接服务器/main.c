/************************************************************
程序说明：
本程序运行后如果gprs模块找到服务商信号，就会连接指定的服务器。
1.将自己的51单片机的串口1连接到GSM的232接口
2.找到程序中前面的#define处，根据说明修改好自己的单片机配置.
3.使用浏览器打开网页http://www.ip138.com/。查询自己的外网ip地址。
4.在光盘中找到 调试工具\socket tool.exe 打开，协议类型：tcp服务器、ip地址本地端口默认。最后点击连接
5.下载程序
6.启动模块,等待信号灯闪烁变慢，如果模块和手机卡正常工作，服务器将收到模块发来的信息

*************************************************************/
#include <REG51.H>
#include <string.h>

#define uchar unsigned char
#define uint unsigned int

//以下是你的51单片机的晶振大小
#define FOSC_110592M
//#define FOSC_12M


//以下用于保存单片机收到模块发来的AT指令，通过这些指令单片机可以判断模块的状态
uchar GsmRcv[50] = {0};
uchar GsmRcvAt[50] = {0}; 
uchar GsmRcvCnt = 0;
uchar GsmAtFlag = 0;
   
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
	uchar i = 0;

	if(RI == 1)	//收到信息
	{

		RI=0;//接收中断信号清零，表示将继续接收
		
		GsmRcv[GsmRcvCnt] = SBUF;
//		Uart1Send(tmp);
		GsmRcvCnt++;
		//收到了完整的AT指令，完整的AT指令是以0x0a 0x0d结尾的。故作此判断，在接收的过程中是否收到0x0a 0x0d
		if(GsmRcv[GsmRcvCnt-2] == 0x0d && GsmRcv[GsmRcvCnt-1] == 0x0a && GsmRcvCnt >= 2)
		{
			//一旦收到0x0a 0x0d，就将数据保存起来。用户主函数的判断。			
			for(i=0; i<GsmRcvCnt; i++)
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


void Uart1Send(uchar c)
{
	SBUF=c;
	while(!TI);//等待发送完成信号（TI=1）出现
	TI=0;	
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

//判断是否启动完成
	GsmAtFlag = 0;
	while(GsmAtFlag == 0)
	{
		Uart1Sends("ATI\r\n");//设置sim300波特率
		DelaySec(1);//延时1秒
	}
	GsmAtFlag = 0;

//检测信号
	while(1)
	{
		Uart1Sends("AT+COPS?\r\n");
		DelaySec(2);//延时1秒
		while(GsmAtFlag == 0);
		if(strstr(GsmRcvAt, "CHINA") )//检测是否收到 CHINA MOBILE 服务商信息。如果收到证明是连接上网络了
		{
			break;
		}		
	}

	while(1)
	{
		Uart1Sends("AT+CIPCLOSE\r\n");
		DelaySec(1);
		Uart1Sends("AT+CIPSHUT\r\n");	
		DelaySec(1);
		Uart1Sends("AT+CLPORT=\"TCP\",\"2022\"\r\n");//发送指令指定本地端口
		DelaySec(1);
		Uart1Sends("AT+CIPSTART=\"TCP\",\"110.212.216.243\",\"8080\"\r\n");//此处修改你建立服务器的IP，服务器端口号8080
		DelaySec(1);
		if(GsmAtFlag == 1 && strstr(GsmRcvAt, "CONNECT OK") )//检测是否收到 CONNECT OK ,如果这连接成功
		{
			Uart1Sends("AT+CIPSEND\r\n");
			DelaySec(1);
			DelaySec(1);
			Uart1Sends("abc123");//向服务器发送数据
	        DelaySec(1);
			Uart1Send(0x1a);//以0x1a结束
		
			DelaySec(15);//延时20秒	
			break;
		}			
	
	}


}
