//STC89C52��Ƭ���������4K�Ĵ洢�ռ䣬��Ϊ8��������ÿ������512�ֽڣ���һ������ʼ��ַΪ��0x2000, ������ַΪ��21FF��
//�ڶ�������ʼ��ַΪ��0x2200, ������ַΪ��23ff��//�ڶ�������ʼ��ַΪ��0x2400, ������ַΪ��25ff���ڰ�������ʼ��ַΪ0x2E00��������ַ��2FFF
#include <reg52.h>
#include <intrins.h>

/******************���������ֽ�******************/     
#define Read_COM    0x01                     //�ֽڶ���������   
#define Prog_COM    0x02                    //�ֽڱ����������   
#define Erase_COM    0x03                   //����������������    
#define En_Wait_TIME    0x81                //���õȴ�ʱ�� ,��ʹ��ISP/IAP      
#define Start_ADDRH 0x20                    //������ַ��λ    
#define Start_ADDRL 0x00                    //������ַ��λ
/****************���⹦�ܼĴ�������****************/
sfr ISP_DATA = 0xe2; 
sfr ISP_ADDRH = 0xe3;   
sfr ISP_ADDRL = 0xe4; 
sfr ISP_CMD = 0xe5; 
sfr ISP_TRIG = 0xe6;    
sfr ISP_CONTR = 0xe7;
/*****************�ر�ISP&IAP����*****************/   
void ISP_IAP_disable(void)   
{   
    ISP_CONTR = 0x00;   
    ISP_CMD = 0x00;    
    ISP_TRIG = 0x00;   
}   
/*********************�ֽڶ�**********************/     
uchar byte_read(uint byte_addr)   
{   
    EA = 0;                                        //���ж�    
    ISP_CONTR = En_Wait_TIME;                   //����ISP&IAP�����͵ȴ�ʱ��    
    ISP_CMD = Read_COM;                         //���ֽڶ�������       
    ISP_ADDRH = (uchar)(byte_addr >> 8);          //�͵�ַ���ֽ�    
    ISP_ADDRL = (uchar)(byte_addr & 0x00ff);    //�͵�ַ���ֽ�        
    ISP_TRIG = 0x46;                            //�ʹ���������0x46   
    ISP_TRIG = 0xB9;                            //�ʹ���������0xB9   
    _nop_();   
    ISP_IAP_disable();                          //�ر�ISP&IAP����    
    EA = 1;                                     //���ж�    
    return (ISP_DATA);   
}     
/*********************�ֽڱ��*********************/   
void Byte_program(uint byte_addr,uchar isp_iap_data)   
{   
    EA = 0;                                     //���ж�    
    ISP_CONTR = En_Wait_TIME;                   //����ISP&IAP�����͵ȴ�ʱ��    
    ISP_CMD = Prog_COM;                         //���ֽڱ��������      
    ISP_ADDRH = (uchar)(byte_addr >> 8);          //�͵�ַ���ֽ�    
    ISP_ADDRL = (uchar)(byte_addr & 0x00ff);    //�͵�ַ���ֽ�        
    ISP_DATA = isp_iap_data;                    //�����ݽ�ISP_DATA    
    ISP_TRIG = 0x46;                            //�ʹ���������0x46   
    ISP_TRIG = 0xB9;                            //�ʹ���������0xB9   
    _nop_();   
    ISP_IAP_disable();                          //�ر�ISP&IAP����    
    EA = 1;                                     //���ж�       
}   
   
/*********************��������*********************/   
void Sector_erase(uint sector_addr)   
{   
    EA = 0;                                     //���ж�    
    ISP_CONTR = En_Wait_TIME;                   //����ISP&IAP;���͵ȴ�ʱ��    
    ISP_CMD = Erase_COM;                        //����������������      
    ISP_ADDRH = (uchar)(sector_addr >> 8);       //�͵�ַ���ֽ�    
    ISP_ADDRL = (uchar)(sector_addr & 0X00FF);    //�͵�ַ���ֽ�        
    ISP_TRIG = 0X46;                            //�ʹ���������0x46  
    ISP_TRIG = 0XB9;                            //�ʹ���������0xB9   
    _nop_();   
    ISP_IAP_disable();                          //�ر�ISP&IAP����    
    EA = 1;   
} 
/******************�����ݱ��浽��Ƭ���ڲ�eeprom��******************/
void write_eeprom()	//��������
{
	Sector_erase(0x2000);
	Byte_program(0x2000, wei_x);
	Byte_program(0x2001, wei_x >> 8);
	Byte_program(0x2002, wei_x >> 16);

}

 /******************�����ݴӵ�Ƭ���ڲ�eeprom�ж�����*****************/
void read_eeprom()	 //������������
{
	wei_x = byte_read(0x2002);
	wei_x<<= 8;
	wei_x |= byte_read(0x2001);  
	wei_x <<= 8;
	wei_x|= byte_read(0x2000);



}

