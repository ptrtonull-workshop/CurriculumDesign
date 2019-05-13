//STC89C52单片机自身带有4K的存储空间，分为8个扇区，每个扇区512字节，第一扇区起始地址为：0x2000, 结束地址为：21FF，
//第二扇区起始地址为：0x2200, 结束地址为：23ff，//第二扇区起始地址为：0x2400, 结束地址为：25ff，第八扇区起始地址为0x2E00，结束地址是2FFF
#include <reg52.h>
#include <intrins.h>

/******************定义命令字节******************/     
#define Read_COM    0x01                     //字节读数据命令   
#define Prog_COM    0x02                    //字节编程数据命令   
#define Erase_COM    0x03                   //扇区擦除数据命令    
#define En_Wait_TIME    0x81                //设置等待时间 ,并使能ISP/IAP      
#define Start_ADDRH 0x20                    //扇区地址高位    
#define Start_ADDRL 0x00                    //扇区地址低位
/****************特殊功能寄存器声明****************/
sfr ISP_DATA = 0xe2; 
sfr ISP_ADDRH = 0xe3;   
sfr ISP_ADDRL = 0xe4; 
sfr ISP_CMD = 0xe5; 
sfr ISP_TRIG = 0xe6;    
sfr ISP_CONTR = 0xe7;
/*****************关闭ISP&IAP功能*****************/   
void ISP_IAP_disable(void)   
{   
    ISP_CONTR = 0x00;   
    ISP_CMD = 0x00;    
    ISP_TRIG = 0x00;   
}   
/*********************字节读**********************/     
uchar byte_read(uint byte_addr)   
{   
    EA = 0;                                        //关中断    
    ISP_CONTR = En_Wait_TIME;                   //开启ISP&IAP，并送等待时间    
    ISP_CMD = Read_COM;                         //送字节读命令字       
    ISP_ADDRH = (uchar)(byte_addr >> 8);          //送地址高字节    
    ISP_ADDRL = (uchar)(byte_addr & 0x00ff);    //送地址低字节        
    ISP_TRIG = 0x46;                            //送触发命令字0x46   
    ISP_TRIG = 0xB9;                            //送触发命令字0xB9   
    _nop_();   
    ISP_IAP_disable();                          //关闭ISP&IAP功能    
    EA = 1;                                     //开中断    
    return (ISP_DATA);   
}     
/*********************字节编程*********************/   
void Byte_program(uint byte_addr,uchar isp_iap_data)   
{   
    EA = 0;                                     //关中断    
    ISP_CONTR = En_Wait_TIME;                   //开启ISP&IAP，并送等待时间    
    ISP_CMD = Prog_COM;                         //送字节编程命令字      
    ISP_ADDRH = (uchar)(byte_addr >> 8);          //送地址高字节    
    ISP_ADDRL = (uchar)(byte_addr & 0x00ff);    //送地址低字节        
    ISP_DATA = isp_iap_data;                    //送数据进ISP_DATA    
    ISP_TRIG = 0x46;                            //送触发命令字0x46   
    ISP_TRIG = 0xB9;                            //送触发命令字0xB9   
    _nop_();   
    ISP_IAP_disable();                          //关闭ISP&IAP功能    
    EA = 1;                                     //开中断       
}   
   
/*********************扇区擦除*********************/   
void Sector_erase(uint sector_addr)   
{   
    EA = 0;                                     //关中断    
    ISP_CONTR = En_Wait_TIME;                   //开启ISP&IAP;并送等待时间    
    ISP_CMD = Erase_COM;                        //送扇区擦除命令字      
    ISP_ADDRH = (uchar)(sector_addr >> 8);       //送地址高字节    
    ISP_ADDRL = (uchar)(sector_addr & 0X00FF);    //送地址低字节        
    ISP_TRIG = 0X46;                            //送触发命令字0x46  
    ISP_TRIG = 0XB9;                            //送触发命令字0xB9   
    _nop_();   
    ISP_IAP_disable();                          //关闭ISP&IAP功能    
    EA = 1;   
} 
/******************把数据保存到单片机内部eeprom中******************/
void write_eeprom()	//保存数据
{
	Sector_erase(0x2000);
	Byte_program(0x2000, wei_x);
	Byte_program(0x2001, wei_x >> 8);
	Byte_program(0x2002, wei_x >> 16);

}

 /******************把数据从单片机内部eeprom中读出来*****************/
void read_eeprom()	 //读出保存数据
{
	wei_x = byte_read(0x2002);
	wei_x<<= 8;
	wei_x |= byte_read(0x2001);  
	wei_x <<= 8;
	wei_x|= byte_read(0x2000);



}

