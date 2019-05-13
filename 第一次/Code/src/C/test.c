#include "reg52.h" //µ¥Æ¬»úÍ·ÎÄ¼þ
#include ¡°string.h"
#include ¡°lcd1602_drv.h¡±
#define uchar unsigned char
#define uint unsigned int
#define Rx_data_length 110
uchar Admin_num£Û11£Ý=¡°xxxxxxxxxxx¡±;
//ÊÖ»úºÅÂë uchar i£¬j;¡
bit Response_receive_SMS_flag=0;
sbit RS_1602=P2^6; //1602Êý¾Ý/ÃüÁîÑ¡ÔñÒý½Å
sbit LCD_RW=P2^5; //1602¶ÁÐ´Òý½Å
bit E_1602=P2^7; //1602Ê¹ÄÜÒý½Å
uchar Rx_bit£¬i;
uchar xdata Rx_data£ÛRx_data_length£Ý;
uchar w£Û£Ý=¡°WaiTIng ¡£¡£¡£¡£¡£¡£ ¡±;

void Response_receive_SMS£¨void£©;
void Uart_SendChar£¨uchar ch£©;
void Uart_SendString£¨uchar *String£©;
void uart_init£¨void£©;
void Clear_Rxdata£¨uchar length£©;

void delay£¨uint xms£©
{
	uint i£¬j; for£¨i=xms;i¡·0;i--£©
	for£¨j=100;j¡·0;j--£©;
}
void main£¨void£©
{
¡¡¡¡uint aa=0£» EA=1; //¿ª×ÜÖÐ¶Ï
¡¡  LCD_RW=0; //LCD RW Ö÷³ÌÐò½ÓµØÒ»Ö±µÈÓÚ0
¡¡¡¡uart_init£¨£©; //´®¿Ú³õÊ¼»¯
¡¡¡¡lcd_init£¨£©; //Òº¾§ÆÁÏÔÊ¾³õÊ¼»¯
¡¡¡¡Rx_bit=0;
¡¡¡¡Uart_SendString£¨¡°AT+CLIP=1\r\n¡±£©;
¡¡¡¡delay£¨500£©;
¡¡¡¡Uart_SendString£¨¡°AT+CMGF=1\r\n¡±£©; //ÉèÖÃsim900Ä£¿éÎªÓ¢ÎÄ·½Ê½·¢ËÍ¶ÌÐÅ
¡¡¡¡delay£¨500£©;
¡¡¡¡Uart_SendString£¨¡°AT+CMGD=1\r\n¡±£©; //Çå³ýËùÓÐ¶ÌÐÅ
¡¡¡¡delay£¨500£©;
¡¡¡¡Uart_SendString£¨¡°AT+CSCS=\¡±GSM\¡°\r¡±£©; //ÉèÖÃsim900Ä£¿éGSM×Ö·û¼¯
¡¡¡¡delay£¨500£©;
¡¡¡¡Uart_SendString£¨¡°AT+CMGF=1\r¡±£©; //ÉèÖÃsim900Ä£¿éÎªÓ¢ÎÄ·½Ê½·¢ËÍ¶ÌÐÅ
¡¡¡¡delay£¨500£©;
¡¡¡¡Clear_Rxdata£¨Rx_data_length£©;
¡¡¡¡delay£¨500£©;
¡¡¡¡memset£¨Rx_data£¬¡® ¡¯£¬sizeof£¨Rx_data£©£©; //Rx_dataÊý×éÖÐÔªËØ¶¼Îª¿Õ¸ñ
¡¡¡¡write_1602com£¨one£©;
¡¡¡¡for£¨i=0;i¡¶16;i++£©
¡¡¡¡{
¡¡¡¡	while£¨1£©
¡¡¡¡{
¡¡¡¡EA=1;
¡¡¡¡EX0=1; //¿ªÍâ²¿ÖÐ¶Ï0
¡¡¡¡IT0=0; //Âö³å´¥·¢·½Ê½
¡¡¡¡Response_receive_SMS£¨£©; //Ñ­»·¼ì²âÊÇ·ñÊÕµ½¶ÌÐÅ£¬ÈôÊÕµ½¶ÌÐÅÔò Response_receive_SMS_flag==1
¡¡¡¡delay£¨100£©;
¡¡¡¡Rx_bit=0;
¡¡¡¡if£¨Response_receive_SMS_flag==1£©
¡¡¡¡{
¡¡¡¡Uart_SendString£¨¡°AT+CMGR=1\r\n¡±£©; //¶ÌÐÅ¶ÁÈ¡
¡¡¡¡delay£¨2000£©;
¡¡¡¡write_1602com£¨one£©;
¡¡¡¡for£¨i=0;i¡¶16;i++£©
¡¡¡¡{
¡¡¡¡	write_1602dat£¨Rx_data£Û69+i£Ý£©;
¡¡¡¡}
¡¡¡¡if£¨Rx_data£Û69£Ý==¡®x¡¯&&Rx_data£Û70£Ý==¡®x¡¯&&Rx_data£Û71£Ý==¡®ax¡¯&&Rx_data£Û72£Ý==¡®x¡¯&&Rx_data£Û73£Ý==¡®x¡¯£© //ÅÐ¶ÏµÄ¶ÌÐÅÄÚÈÝ£¬¿ÉÒÔ²»Ö¹5Î»

¡¡¡¡{

¡¡¡¡aa=1£»

¡¡¡¡}

¡¡¡¡Response_receive_SMS_flag=0;

¡¡¡¡Clear_Rxdata£¨Rx_data_length£©;

¡¡¡¡delay£¨100£©;

¡¡¡¡Uart_SendString£¨¡°AT+CMGD=1\r\n¡±£©; //Çå³ýËùÓÐ¶ÌÐÅ
¡¡¡¡delay£¨100£©;
¡¡¡¡}
¡¡¡¡delay£¨1000£©;
¡¡¡¡if£¨aa==1£©
¡¡¡¡{
¡¡¡¡delay£¨1000£©;
¡¡¡¡Uart_SendString£¨¡°AT+CMGS=\¡±¡°£©;
¡¡¡¡for£¨j=0;j¡¶11;j++£©
¡¡¡¡{
¡¡¡¡SBUF=Admin_num£Ûj£Ý;
¡¡¡¡while£¨TI==0£©;
¡¡¡¡TI=0;
¡¡¡¡}
¡¡¡¡Uart_SendString£¨¡°\¡±\r¡°£©;
¡¡¡¡delay£¨200£©;
¡¡¡¡Uart_SendString£¨¡±xxx¡°£©; //·µ»ØµÄ¶ÌÐÅÄÚÈÝ
¡¡¡¡delay£¨300£©;
¡¡¡¡Uart_SendChar£¨0x1a£©;
¡¡¡¡delay£¨1000£©;
¡¡¡¡aa=0£»}
¡¡¡¡}
¡¡¡¡}
¡¡¡¡void uart£¨£© interrupt 4
¡¡¡¡{
¡¡¡¡ES=0;
¡¡¡¡if£¨RI==1£© //µ±Ó²¼þ½Ó ÊÕµ½Ò»¸öÊý¾ÝÊ±£¬RI»áÖÃÎ»
¡¡¡¡{
¡¡¡¡if£¨SBUF£¡=0x0d&&SBUF£¡=0x0a&&SBUF£¡=¡® ¡¯£© //È¥³ýËùÓÐµÄ¿Õ¸ñ
¡¡¡¡{
¡¡¡¡Rx_data£ÛRx_bit£Ý=SBUF;
¡¡¡¡Rx_bit++;
¡¡¡¡}
¡¡¡¡if£¨Rx_bit==Rx_data_length£©
¡¡¡¡{
¡¡¡¡Rx_bit=0;
¡¡¡¡}
¡¡¡¡RI=0;
¡¡¡¡}
¡¡¡¡ES=1;
¡¡¡¡}
¡¡¡¡uchar i=0;
¡¡¡¡for£¨i=0;i¡¶=Rx_data_length;i++£©
¡¡¡¡{
¡¡¡¡if£¨Rx_data£Ûi£Ý ==¡®+¡¯
¡¡¡¡&&Rx_data£Ûi+1£Ý==¡®C¡¯
¡¡¡¡&&Rx_data£Ûi+2£Ý==¡®M¡¯
¡¡¡¡&&Rx_data£Ûi+3£Ý==¡®T¡¯
¡¡¡¡&&Rx_data£Ûi+4£Ý==¡®I¡¯
¡¡¡¡&&Rx_data£Ûi+5£Ý==¡®£º¡¯£©
¡¡¡¡{
¡¡¡¡Response_receive_SMS_flag=1;
¡¡¡¡return;
¡¡¡¡}
¡¡¡¡}
¡¡¡¡Response_receive_SMS_flag=0;
¡¡¡¡}
¡¡¡¡/********************************************************************
¡¡¡¡* Ãû³Æ £º Uart_SendChar£¨uchar ch£©
¡¡¡¡* ¹¦ÄÜ £º Ïò´®¿Ú·¢ËÍÒ»¸ö×Ö·û
¡¡¡¡* ÊäÈë £º ÎÞ
¡¡¡¡* Êä³ö £º ÎÞ
¡¡¡¡***********************************************************************/
¡¡¡¡void Uart_SendChar£¨uchar ch£©
¡¡¡¡{
¡¡¡¡SBUF=ch;
¡¡¡¡while£¨TI==0£©;
¡¡¡¡TI=0;
¡¡¡¡}
¡¡¡¡void Response_receive_SMS£¨void£©
¡¡¡¡{
¡¡¡¡/********************************************************************
¡¡¡¡* Ãû³Æ £º Uart_SendChar£¨uchar ch£©
¡¡¡¡* ¹¦ÄÜ £º Ïò´®¿Ú·¢ËÍÒ»¸ö×Ö·û´®
¡¡¡¡* ÊäÈë £º ÎÞ
¡¡¡¡* Êä³ö £º ÎÞ
¡¡¡¡***********************************************************************/
¡¡¡¡void Uart_SendString£¨uchar *String£©
¡¡¡¡{
¡¡¡¡while £¨*String £¡=¡®\0¡¯£© //×Ö·û´®½áÊø±êÖ¾ \0
¡¡¡¡{
¡¡¡¡Uart_SendChar£¨*String£©; String++;
¡¡¡¡}
¡¡¡¡}
¡¡¡¡/********************************************************************
¡¡¡¡* Ãû³Æ £º uart_init£¨void£©
¡¡¡¡* ¹¦ÄÜ £º ´®¿Ú³õÊ¼»¯³ÌÐò
¡¡¡¡* ÊäÈë £º ÎÞ
¡¡¡¡* Êä³ö £º ÎÞ
¡¡¡¡***********************************************************************/
¡¡¡¡void uart_init£¨void£© //³õÊ¼»¯uart
¡¡¡¡{
¡¡¡¡TMOD = 0x20; //¶¨Ê±Æ÷1¹¤×÷Ä£Ê½2£¬8Î»¿É×Ô¶¯ÖØÔØ³õÖµ£¬³£°Ñ¶¨Ê±1ÒÔÄ£Ê½2×÷Îª´®ÐÐ¿Ú²¨ÌØÂÊ·¢ÉúÆ÷
¡¡¡¡SCON = 0x50; //´®¿ÚÑ¡Ôñ¹¤×÷Ä£Ê½1Ê¹ÄÜ½ÓÊÕ£¬ÔÊÐí·¢ËÍ£¬ÔÊÐí½ÓÊÕ
¡¡¡¡TH1 = 0xFD; //ÓÃ11.0592 MHz²¨ÌØÂÊ 9600
¡¡¡¡TL1 = 0xFD;
¡¡¡¡TR1 = 1; //´ò¿ªÖÐÊ±Æ÷
¡¡¡¡ES=1; //´ò¿ª´®¿ÚÖÐ¶Ï
¡¡¡¡}
¡¡¡¡/********************************************************************
¡¡¡¡* Ãû³Æ £º Clear_Rxdata£¨uchar length£©
¡¡¡¡* ¹¦ÄÜ £º Çå¿Õ½ÓÊÕ»º´æÊý×é
¡¡¡¡* ÊäÈë £º ÎÞ
¡¡¡¡* Êä³ö £º ÎÞ
¡¡¡¡***********************************************************************/
¡¡¡¡void Clear_Rxdata£¨uchar length£© //Çå¿Õ½ÓÊÕ»º´æÊý×é
¡¡¡¡{
¡¡¡¡uchar Bit;
¡¡¡¡for£¨Bit=0;Bit¡¶length;Bit++£©
¡¡¡¡{
¡¡¡¡Rx_data£ÛBit£Ý=0x30; // asciiÂë±íÖÐÊ®½øÖÆ48¶ÔÓ¦µÄ×Ö·ûÎª0
¡¡¡¡delay£¨50£©;
¡¡¡¡}
¡¡¡¡Rx_bit=0;
¡¡¡¡}