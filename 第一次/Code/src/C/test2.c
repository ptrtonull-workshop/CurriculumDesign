#ifndef __LCD1602_DRV_H__
#define __LCD1602_DRV_H__
#define uchar unsigned char
#define uint unsigned int #define one 0x80 //第一行的初始位置
#define two 0x80+0x40
void write_1602com(uchar com);
void write_1602dat(uchar dat);
void lcd_init();
#endif