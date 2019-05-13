#include《reg52.h》
#include “lcd1602_drv.h”
sbit RS_1602=P2^6;
sbit LCD_RW=P2^5; //LCD RW 主程序接地一直等于0
sbit E_1602=P2^7;�
uchar aa，jj;
　　//①写命令子程序
void write_1602com（uchar com） //液晶写入指令函数
{
　　RS_1602=0; //置为写入命令
　　P0=com; //送入数据
　　delay（1）;
　　E_1602=1;
　　delay（1）;
　　E_1602=0;
}
　　//②写数据子程序
　　void write_1602dat（uchar dat）
　　{
　　RS_1602=1; //置为写数据
　　P0=dat; //送入数据
　　delay（1）;
　　E_1602=1;
　　delay（1）;
　　E_1602=0;
　　}
　　void lcd_init（void）
　　{
　　write_1602com（0x38）; //16*2 5*7点阵 8位数据线
　　delay（5）;
　　write_1602com（0x38）;
　　delay（5）;
　　write_1602com（0x38）;
　　delay（5）;
　　write_1602com（0x08）;
　　write_1602com（0x0c）; //开显示 不显示光标 不闪烁
　　write_1602com（0x06）; //显示不移动 光标右移
　　write_1602com（0x01）; // 清屏
　　}