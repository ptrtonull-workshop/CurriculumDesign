

sbit CSN  =P1^0;//define I/O prot
sbit MOSI =P1^1;
sbit IRQ  =P1^2;
sbit MISO =P1^3;
sbit SCK  =P1^4;
sbit CE   =P1^5; 

uchar idata TxBuf[32]=
{'0','0','0','0','0','0','0','0',
'0','0','0','0','0','0','0','0',
'0','0','0','0','0','0','3','0',
'5','0','0','0','0','0','0','0'
};
uchar sta;//count,tf;//i,j;
/*********************************************NRF24L01************************************************/
#define TX_ADR_WIDTH    5   	// 5 uints TX address width
#define RX_ADR_WIDTH    5   	// 5 uints RX address width
#define TX_PLOAD_WIDTH  32  	// 20 uints TX payload
#define RX_PLOAD_WIDTH  32  	// 20 uints TX payload
uchar  TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//本地地址
uchar  RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//接收地址
/***************************************NRF24L01寄存器指令*******************************************/
#define READ_REG        0x00  	// 读寄存器指令
#define WRITE_REG       0x20 	// 写寄存器指令
#define RD_RX_PLOAD     0x61  	// 读取接收数据指令
#define WR_TX_PLOAD     0xA0  	// 写待发数据指令
#define FLUSH_TX        0xE1 	// 冲洗发送 FIFO指令
#define FLUSH_RX        0xE2  	// 冲洗接收 FIFO指令
#define REUSE_TX_PL     0xE3  	// 定义重复装载数据指令
#define NOP1            0xFF  	// 保留
/*************************************SPI(nRF24L01)寄存器地址****************************************/
#define CONFIG          0x00  // 配置收发状态，CRC校验模式以及收发状态响应方式
#define EN_AA           0x01  // 自动应答功能设置
#define EN_RXADDR       0x02  // 可用信道设置
#define SETUP_AW        0x03  // 收发地址宽度设置
#define SETUP_RETR      0x04  // 自动重发功能设置
#define RF_CH           0x05  // 工作频率设置
#define RF_SETUP        0x06  // 发射速率、功耗功能设置
#define STATUS          0x07  // 状态寄存器
#define OBSERVE_TX      0x08  // 发送监测功能
#define CD              0x09  // 地址检测           
#define RX_ADDR_P0      0x0A  // 频道0接收数据地址
#define RX_ADDR_P1      0x0B  // 频道1接收数据地址
#define RX_ADDR_P2      0x0C  // 频道2接收数据地址
#define RX_ADDR_P3      0x0D  // 频道3接收数据地址
#define RX_ADDR_P4      0x0E  // 频道4接收数据地址
#define RX_ADDR_P5      0x0F  // 频道5接收数据地址
#define TX_ADDR         0x10  // 发送地址寄存器
#define RX_PW_P0        0x11  // 接收频道0接收数据长度
#define RX_PW_P1        0x12  // 接收频道0接收数据长度
#define RX_PW_P2        0x13  // 接收频道0接收数据长度
#define RX_PW_P3        0x14  // 接收频道0接收数据长度
#define RX_PW_P4        0x15  // 接收频道0接收数据长度
#define RX_PW_P5        0x16  // 接收频道0接收数据长度
#define FIFO_STATUS     0x17  // FIFO栈入栈出状态寄存器设置

void delay1ms(uint z)
{
	uchar y;
	while(z--)
		for(y=110;y>0;y--);
}
/****************************************************/



/*************************************************/
/*函数：char SPI_RW(char data)*/
/*功能：NRF24L01的SPI写时序*/
/****************************************************************************************************/
uchar SPI_RW(uchar dt)
{
    uchar i;
	MISO=1;
    for(i=0;i<8;i++)
    {
     	MOSI=(dt & 0x80);
        dt = (dt << 1);
	//	 delay1ms(1);
         SCK=1;
		
	//	  delay1ms(1);
		 dt |= MISO;
         SCK=0;
//		   delay1ms(1);
		

		 
    }
    return(dt);
}
/****************************************************************************************************/
/*函数：char SPI_Read(char reg)*/
/*功能：NRF24L01的SPI时序*/
/****************************************************************************************************/
uchar SPI_Read(uchar reg)
{
    uchar reg_val;
    CSN=0;
	delay1ms(1);
    SPI_RW(reg);
    reg_val = SPI_RW(0);
	delay1ms(1);
    CSN=1;
    return(reg_val);
}
/****************************************************************************************************/
/*功能：NRF24L01读写寄存器函数*/
/****************************************************************************************************/
uchar SPI_RW_Reg(uchar reg, uchar value)
{
    uchar status;
    CSN=0;
    status = SPI_RW(reg);
    SPI_RW(value);
    CSN=1;
    return(status);
}
/****************************************************************************************************/
/*函数：uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)*/
/*功能: 用于读数据，reg：为寄存器地址，pBuf：为待读出数据地址，uchars：读出数据的个数*/
/****************************************************************************************************/
uchar SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
    int status1,uchar_ctr;
       CSN=0;
    status1 = SPI_RW(reg);
    for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
        pBuf[uchar_ctr] = SPI_RW(0);
      CSN=1;
    return(status1);    
}
/*********************************************************************************************************/
/*函数：uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)*/
/*功能: 用于写数据：为寄存器地址，pBuf：为待写入数据地址，uchars：写入数据的个数*/
/*********************************************************************************************************/
uchar SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
    uchar status1,uchar_ctr;
    CSN=0;
    status1 = SPI_RW(reg);
    for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
    SPI_RW(*pBuf++);
    CSN=1;
    return(status1);
}
/****************************************************************************************************/
/*函数：void SetRX_Mode(void)*/
/*功能：数据接收配置*/
/****************************************************************************************************/
void SetRX_Mode(void)
{
   CE=0;
   SPI_RW_Reg(WRITE_REG + CONFIG,0x0f);// IRQ收发完成中断响应，16位CRC	，主接收
   CE=1;
  delay1ms(530);//注意延时不能太短，否则无法正常工作   
}
/******************************************************************************************************/
/*函数：unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)*/
/*功能：数据读取后放如rx_buf接收缓冲区中*/
/******************************************************************************************************/
uchar nRF24L01_RxPacket(uchar* rx_buf)
{
    uchar revale = 0;

	SetRX_Mode();//设置为接受模式

    sta=SPI_Read(STATUS);
    if(sta&0x40)
    {
        CE=0;
        SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);
        revale = 1;
    }
    SPI_RW_Reg(WRITE_REG+STATUS,sta);
//	 SPI_RW_Reg(WRITE_REG+STATUS,0xff);
    return revale;
}
/***********************************************************************************************************/
/*函数：void nRF24L01_TxPacket(char * tx_buf)*/
/*功能：发送 tx_buf中数据*/
/**********************************************************************************************************/

//发送程序暂时不用
void nRF24L01_TxPacket(uchar * tx_buf)
{
     CE=0;	//停止射频工作
    SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,TX_ADDRESS,TX_ADR_WIDTH);  //写本地地址
    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);//装载接受地址 
    SPI_Write_Buf(WR_TX_PLOAD,tx_buf,TX_PLOAD_WIDTH);			  //转载要发送的数据
    SPI_RW_Reg(WRITE_REG+CONFIG,0x0e);	 //IRQ收发中断响应，16位CRC,发送模式
    CE=1;	 //置高CE，激发数据发送
    delay1ms(130);//注意延时不能太短，否则无法正常工作
}

/****************************************************************************************/
/*NRF24L01初始化*/
/***************************************************************************************/
void init_NRF24L01(void)
{
     CE=0; //ce置0射频电路停止工作
     CSN=1;//CSN 置1，禁止指令操作
     SCK=0;// 禁止读写寄存器
	 IRQ=1;	//中断复位，等待产生中断信号

    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);//写本地地址 
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);//写接收端地址,如果要换用别的频道更改RX_ADDR_P0即可

  /*  SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);//频道0自动	ACK应答允许
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);//允许接收地址只有频道0，如果需要多频道可以参考Page21 */

	 SPI_RW_Reg(WRITE_REG + EN_AA, 0x00);//频道0自动	ACK应答禁止
	 SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);//允许接收地址只有频道0，如果需要多频道可以参考Page21 

//	 SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x00);//禁止自动发送
 
     SPI_RW_Reg(WRITE_REG + RF_CH, 0);//   设置信道工作为2.4GHZ，收发必须一致
     SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);//设置接收数据长度，本次设置为32字节
     SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);//设置发射速率为1MHZ，发射功率为最大值0dB

//    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);// IRQ收发完成中断响应，16位CRC，主接收}

    CE=1;	 //置高CE，激发数据发送
    delay1ms(500);
}





