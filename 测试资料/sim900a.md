### 连接

| SIM900A    | 单片机              |
| ---------- | ------------------- |
| VCC5(电源) | USB-TTL转接线5v     |
| GND(电源)  | USB-TTL转接线的GND  |
| VCC_mcu    | USB-TTL转接线的3.3v |
| GND        | GND                 |
| 5VR        | TXD(P3.1)           |
| 5VT        | RXD(P3.0)           |

单片机通过USB-TTL转接线供电，RXD、TXD不接以免冲突，有关连线的具体信息，[请看这里](https://github.com/ptrtonull-workshop/CurriculumDesign/blob/master/%E6%A8%A1%E5%9D%97%E8%B5%84%E6%96%99/SIM900A/Sim900mini%20V3%20V4/12%EF%BC%8C%E8%B0%83%E8%AF%95%E6%95%99%E7%A8%8B%20%20%E5%BF%85%E7%9C%8B%E8%B5%84%E6%96%99/%7E%241%20SIM900Amini%20V3.7%20TTL%E6%8E%A5%E5%8F%A3%E7%94%B5%E5%B9%B3%E5%8F%98%E6%9B%B4.docx)。

### 代码

执行

```c
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
```

进行初始化

执行一次

```c
Uart1Sends("AT+CSCS=\"GSM\"\r\n");
DelaySec(3);
Uart1Sends("AT+CMGF=1\r\n");
DelaySec(3);
Uart1Sends("AT+CMGS=\"13104610925\"\r\n");//在此处改对方号码
DelaySec(5);
Uart1Sends(sms_text);//默认为abc123，可以修改
Uart1Send(0x1a);
DelaySec(15);
```

来发送一次短信

### 注意

程序中这一块：

```c
#define FOSC_110592M
//#define FOSC_12M
```

如果在我们焊的单片机里无法正常运行的话，可以试着切换一下