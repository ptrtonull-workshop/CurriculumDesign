#include "reg52.h" //单片机头文件
#include “string.h"
#include “lcd1602_drv.h”
#define uchar unsigned char
#define uint unsigned int
#define Rx_data_length 110
uchar Admin_num［11］=“xxxxxxxxxxx”;
//手机号码 uchar i，j;�
bit Response_receive_SMS_flag=0;
sbit RS_1602=P2^6; //1602数据/命令选择引脚
sbit LCD_RW=P2^5; //1602读写引脚
bit E_1602=P2^7; //1602使能引脚
uchar Rx_bit，i;
uchar xdata Rx_data［Rx_data_length］;
uchar w［］=“WaiTIng 。。。。。。 ”;

void Response_receive_SMS（void）;
void Uart_SendChar（uchar ch）;
void Uart_SendString（uchar *String）;
void uart_init（void）;
void Clear_Rxdata（uchar length）;

void delay（uint xms）
{
	uint i，j; for（i=xms;i》0;i--）
	for（j=100;j》0;j--）;
}
void main（void）
{
　　uint aa=0； EA=1; //开总中断
　  LCD_RW=0; //LCD RW 主程序接地一直等于0
　　uart_init（）; //串口初始化
　　lcd_init（）; //液晶屏显示初始化
　　Rx_bit=0;
　　Uart_SendString（“AT+CLIP=1\r\n”）;
　　delay（500）;
　　Uart_SendString（“AT+CMGF=1\r\n”）; //设置sim900模块为英文方式发送短信
　　delay（500）;
　　Uart_SendString（“AT+CMGD=1\r\n”）; //清除所有短信
　　delay（500）;
　　Uart_SendString（“AT+CSCS=\”GSM\“\r”）; //设置sim900模块GSM字符集
　　delay（500）;
　　Uart_SendString（“AT+CMGF=1\r”）; //设置sim900模块为英文方式发送短信
　　delay（500）;
　　Clear_Rxdata（Rx_data_length）;
　　delay（500）;
　　memset（Rx_data，‘ ’，sizeof（Rx_data））; //Rx_data数组中元素都为空格
　　write_1602com（one）;
　　for（i=0;i《16;i++）
　　{
　　	while（1）
　　{
　　EA=1;
　　EX0=1; //开外部中断0
　　IT0=0; //脉冲触发方式
　　Response_receive_SMS（）; //循环检测是否收到短信，若收到短信则 Response_receive_SMS_flag==1
　　delay（100）;
　　Rx_bit=0;
　　if（Response_receive_SMS_flag==1）
　　{
　　Uart_SendString（“AT+CMGR=1\r\n”）; //短信读取
　　delay（2000）;
　　write_1602com（one）;
　　for（i=0;i《16;i++）
　　{
　　	write_1602dat（Rx_data［69+i］）;
　　}
　　if（Rx_data［69］==‘x’&&Rx_data［70］==‘x’&&Rx_data［71］==‘ax’&&Rx_data［72］==‘x’&&Rx_data［73］==‘x’） //判断的短信内容，可以不止5位

　　{

　　aa=1；

　　}

　　Response_receive_SMS_flag=0;

　　Clear_Rxdata（Rx_data_length）;

　　delay（100）;

　　Uart_SendString（“AT+CMGD=1\r\n”）; //清除所有短信
　　delay（100）;
　　}
　　delay（1000）;
　　if（aa==1）
　　{
　　delay（1000）;
　　Uart_SendString（“AT+CMGS=\”“）;
　　for（j=0;j《11;j++）
　　{
　　SBUF=Admin_num［j］;
　　while（TI==0）;
　　TI=0;
　　}
　　Uart_SendString（“\”\r“）;
　　delay（200）;
　　Uart_SendString（”xxx“）; //返回的短信内容
　　delay（300）;
　　Uart_SendChar（0x1a）;
　　delay（1000）;
　　aa=0；}
　　}
　　}
　　void uart（） interrupt 4
　　{
　　ES=0;
　　if（RI==1） //当硬件接 收到一个数据时，RI会置位
　　{
　　if（SBUF！=0x0d&&SBUF！=0x0a&&SBUF！=‘ ’） //去除所有的空格
　　{
　　Rx_data［Rx_bit］=SBUF;
　　Rx_bit++;
　　}
　　if（Rx_bit==Rx_data_length）
　　{
　　Rx_bit=0;
　　}
　　RI=0;
　　}
　　ES=1;
　　}
　　uchar i=0;
　　for（i=0;i《=Rx_data_length;i++）
　　{
　　if（Rx_data［i］ ==‘+’
　　&&Rx_data［i+1］==‘C’
　　&&Rx_data［i+2］==‘M’
　　&&Rx_data［i+3］==‘T’
　　&&Rx_data［i+4］==‘I’
　　&&Rx_data［i+5］==‘：’）
　　{
　　Response_receive_SMS_flag=1;
　　return;
　　}
　　}
　　Response_receive_SMS_flag=0;
　　}
　　/********************************************************************
　　* 名称 ： Uart_SendChar（uchar ch）
　　* 功能 ： 向串口发送一个字符
　　* 输入 ： 无
　　* 输出 ： 无
　　***********************************************************************/
　　void Uart_SendChar（uchar ch）
　　{
　　SBUF=ch;
　　while（TI==0）;
　　TI=0;
　　}
　　void Response_receive_SMS（void）
　　{
　　/********************************************************************
　　* 名称 ： Uart_SendChar（uchar ch）
　　* 功能 ： 向串口发送一个字符串
　　* 输入 ： 无
　　* 输出 ： 无
　　***********************************************************************/
　　void Uart_SendString（uchar *String）
　　{
　　while （*String ！=‘\0’） //字符串结束标志 \0
　　{
　　Uart_SendChar（*String）; String++;
　　}
　　}
　　/********************************************************************
　　* 名称 ： uart_init（void）
　　* 功能 ： 串口初始化程序
　　* 输入 ： 无
　　* 输出 ： 无
　　***********************************************************************/
　　void uart_init（void） //初始化uart
　　{
　　TMOD = 0x20; //定时器1工作模式2，8位可自动重载初值，常把定时1以模式2作为串行口波特率发生器
　　SCON = 0x50; //串口选择工作模式1使能接收，允许发送，允许接收
　　TH1 = 0xFD; //用11.0592 MHz波特率 9600
　　TL1 = 0xFD;
　　TR1 = 1; //打开中时器
　　ES=1; //打开串口中断
　　}
　　/********************************************************************
　　* 名称 ： Clear_Rxdata（uchar length）
　　* 功能 ： 清空接收缓存数组
　　* 输入 ： 无
　　* 输出 ： 无
　　***********************************************************************/
　　void Clear_Rxdata（uchar length） //清空接收缓存数组
　　{
　　uchar Bit;
　　for（Bit=0;Bit《length;Bit++）
　　{
　　Rx_data［Bit］=0x30; // ascii码表中十进制48对应的字符为0
　　delay（50）;
　　}
　　Rx_bit=0;
　　}