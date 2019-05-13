#include "reg52.h" //��Ƭ��ͷ�ļ�
#include ��string.h"
#include ��lcd1602_drv.h��
#define uchar unsigned char
#define uint unsigned int
#define Rx_data_length 110
uchar Admin_num��11��=��xxxxxxxxxxx��;
//�ֻ����� uchar i��j;�
bit Response_receive_SMS_flag=0;
sbit RS_1602=P2^6; //1602����/����ѡ������
sbit LCD_RW=P2^5; //1602��д����
bit E_1602=P2^7; //1602ʹ������
uchar Rx_bit��i;
uchar xdata Rx_data��Rx_data_length��;
uchar w�ۣ�=��WaiTIng ������������ ��;

void Response_receive_SMS��void��;
void Uart_SendChar��uchar ch��;
void Uart_SendString��uchar *String��;
void uart_init��void��;
void Clear_Rxdata��uchar length��;

void delay��uint xms��
{
	uint i��j; for��i=xms;i��0;i--��
	for��j=100;j��0;j--��;
}
void main��void��
{
����uint aa=0�� EA=1; //�����ж�
��  LCD_RW=0; //LCD RW ������ӵ�һֱ����0
����uart_init����; //���ڳ�ʼ��
����lcd_init����; //Һ������ʾ��ʼ��
����Rx_bit=0;
����Uart_SendString����AT+CLIP=1\r\n����;
����delay��500��;
����Uart_SendString����AT+CMGF=1\r\n����; //����sim900ģ��ΪӢ�ķ�ʽ���Ͷ���
����delay��500��;
����Uart_SendString����AT+CMGD=1\r\n����; //������ж���
����delay��500��;
����Uart_SendString����AT+CSCS=\��GSM\��\r����; //����sim900ģ��GSM�ַ���
����delay��500��;
����Uart_SendString����AT+CMGF=1\r����; //����sim900ģ��ΪӢ�ķ�ʽ���Ͷ���
����delay��500��;
����Clear_Rxdata��Rx_data_length��;
����delay��500��;
����memset��Rx_data���� ����sizeof��Rx_data����; //Rx_data������Ԫ�ض�Ϊ�ո�
����write_1602com��one��;
����for��i=0;i��16;i++��
����{
����	while��1��
����{
����EA=1;
����EX0=1; //���ⲿ�ж�0
����IT0=0; //���崥����ʽ
����Response_receive_SMS����; //ѭ������Ƿ��յ����ţ����յ������� Response_receive_SMS_flag==1
����delay��100��;
����Rx_bit=0;
����if��Response_receive_SMS_flag==1��
����{
����Uart_SendString����AT+CMGR=1\r\n����; //���Ŷ�ȡ
����delay��2000��;
����write_1602com��one��;
����for��i=0;i��16;i++��
����{
����	write_1602dat��Rx_data��69+i�ݣ�;
����}
����if��Rx_data��69��==��x��&&Rx_data��70��==��x��&&Rx_data��71��==��ax��&&Rx_data��72��==��x��&&Rx_data��73��==��x���� //�жϵĶ������ݣ����Բ�ֹ5λ

����{

����aa=1��

����}

����Response_receive_SMS_flag=0;

����Clear_Rxdata��Rx_data_length��;

����delay��100��;

����Uart_SendString����AT+CMGD=1\r\n����; //������ж���
����delay��100��;
����}
����delay��1000��;
����if��aa==1��
����{
����delay��1000��;
����Uart_SendString����AT+CMGS=\������;
����for��j=0;j��11;j++��
����{
����SBUF=Admin_num��j��;
����while��TI==0��;
����TI=0;
����}
����Uart_SendString����\��\r����;
����delay��200��;
����Uart_SendString����xxx����; //���صĶ�������
����delay��300��;
����Uart_SendChar��0x1a��;
����delay��1000��;
����aa=0��}
����}
����}
����void uart���� interrupt 4
����{
����ES=0;
����if��RI==1�� //��Ӳ���� �յ�һ������ʱ��RI����λ
����{
����if��SBUF��=0x0d&&SBUF��=0x0a&&SBUF��=�� ���� //ȥ�����еĿո�
����{
����Rx_data��Rx_bit��=SBUF;
����Rx_bit++;
����}
����if��Rx_bit==Rx_data_length��
����{
����Rx_bit=0;
����}
����RI=0;
����}
����ES=1;
����}
����uchar i=0;
����for��i=0;i��=Rx_data_length;i++��
����{
����if��Rx_data��i�� ==��+��
����&&Rx_data��i+1��==��C��
����&&Rx_data��i+2��==��M��
����&&Rx_data��i+3��==��T��
����&&Rx_data��i+4��==��I��
����&&Rx_data��i+5��==��������
����{
����Response_receive_SMS_flag=1;
����return;
����}
����}
����Response_receive_SMS_flag=0;
����}
����/********************************************************************
����* ���� �� Uart_SendChar��uchar ch��
����* ���� �� �򴮿ڷ���һ���ַ�
����* ���� �� ��
����* ��� �� ��
����***********************************************************************/
����void Uart_SendChar��uchar ch��
����{
����SBUF=ch;
����while��TI==0��;
����TI=0;
����}
����void Response_receive_SMS��void��
����{
����/********************************************************************
����* ���� �� Uart_SendChar��uchar ch��
����* ���� �� �򴮿ڷ���һ���ַ���
����* ���� �� ��
����* ��� �� ��
����***********************************************************************/
����void Uart_SendString��uchar *String��
����{
����while ��*String ��=��\0���� //�ַ���������־ \0
����{
����Uart_SendChar��*String��; String++;
����}
����}
����/********************************************************************
����* ���� �� uart_init��void��
����* ���� �� ���ڳ�ʼ������
����* ���� �� ��
����* ��� �� ��
����***********************************************************************/
����void uart_init��void�� //��ʼ��uart
����{
����TMOD = 0x20; //��ʱ��1����ģʽ2��8λ���Զ����س�ֵ�����Ѷ�ʱ1��ģʽ2��Ϊ���пڲ����ʷ�����
����SCON = 0x50; //����ѡ����ģʽ1ʹ�ܽ��գ������ͣ��������
����TH1 = 0xFD; //��11.0592 MHz������ 9600
����TL1 = 0xFD;
����TR1 = 1; //����ʱ��
����ES=1; //�򿪴����ж�
����}
����/********************************************************************
����* ���� �� Clear_Rxdata��uchar length��
����* ���� �� ��ս��ջ�������
����* ���� �� ��
����* ��� �� ��
����***********************************************************************/
����void Clear_Rxdata��uchar length�� //��ս��ջ�������
����{
����uchar Bit;
����for��Bit=0;Bit��length;Bit++��
����{
����Rx_data��Bit��=0x30; // ascii�����ʮ����48��Ӧ���ַ�Ϊ0
����delay��50��;
����}
����Rx_bit=0;
����}