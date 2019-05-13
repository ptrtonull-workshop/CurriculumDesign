

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
uchar  TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���ص�ַ
uchar  RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���յ�ַ
/***************************************NRF24L01�Ĵ���ָ��*******************************************/
#define READ_REG        0x00  	// ���Ĵ���ָ��
#define WRITE_REG       0x20 	// д�Ĵ���ָ��
#define RD_RX_PLOAD     0x61  	// ��ȡ��������ָ��
#define WR_TX_PLOAD     0xA0  	// д��������ָ��
#define FLUSH_TX        0xE1 	// ��ϴ���� FIFOָ��
#define FLUSH_RX        0xE2  	// ��ϴ���� FIFOָ��
#define REUSE_TX_PL     0xE3  	// �����ظ�װ������ָ��
#define NOP1            0xFF  	// ����
/*************************************SPI(nRF24L01)�Ĵ�����ַ****************************************/
#define CONFIG          0x00  // �����շ�״̬��CRCУ��ģʽ�Լ��շ�״̬��Ӧ��ʽ
#define EN_AA           0x01  // �Զ�Ӧ��������
#define EN_RXADDR       0x02  // �����ŵ�����
#define SETUP_AW        0x03  // �շ���ַ�������
#define SETUP_RETR      0x04  // �Զ��ط���������
#define RF_CH           0x05  // ����Ƶ������
#define RF_SETUP        0x06  // �������ʡ����Ĺ�������
#define STATUS          0x07  // ״̬�Ĵ���
#define OBSERVE_TX      0x08  // ���ͼ�⹦��
#define CD              0x09  // ��ַ���           
#define RX_ADDR_P0      0x0A  // Ƶ��0�������ݵ�ַ
#define RX_ADDR_P1      0x0B  // Ƶ��1�������ݵ�ַ
#define RX_ADDR_P2      0x0C  // Ƶ��2�������ݵ�ַ
#define RX_ADDR_P3      0x0D  // Ƶ��3�������ݵ�ַ
#define RX_ADDR_P4      0x0E  // Ƶ��4�������ݵ�ַ
#define RX_ADDR_P5      0x0F  // Ƶ��5�������ݵ�ַ
#define TX_ADDR         0x10  // ���͵�ַ�Ĵ���
#define RX_PW_P0        0x11  // ����Ƶ��0�������ݳ���
#define RX_PW_P1        0x12  // ����Ƶ��0�������ݳ���
#define RX_PW_P2        0x13  // ����Ƶ��0�������ݳ���
#define RX_PW_P3        0x14  // ����Ƶ��0�������ݳ���
#define RX_PW_P4        0x15  // ����Ƶ��0�������ݳ���
#define RX_PW_P5        0x16  // ����Ƶ��0�������ݳ���
#define FIFO_STATUS     0x17  // FIFOջ��ջ��״̬�Ĵ�������

void delay1ms(uint z)
{
	uchar y;
	while(z--)
		for(y=110;y>0;y--);
}
/****************************************************/



/*************************************************/
/*������char SPI_RW(char data)*/
/*���ܣ�NRF24L01��SPIдʱ��*/
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
/*������char SPI_Read(char reg)*/
/*���ܣ�NRF24L01��SPIʱ��*/
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
/*���ܣ�NRF24L01��д�Ĵ�������*/
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
/*������uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)*/
/*����: ���ڶ����ݣ�reg��Ϊ�Ĵ�����ַ��pBuf��Ϊ���������ݵ�ַ��uchars���������ݵĸ���*/
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
/*������uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)*/
/*����: ����д���ݣ�Ϊ�Ĵ�����ַ��pBuf��Ϊ��д�����ݵ�ַ��uchars��д�����ݵĸ���*/
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
/*������void SetRX_Mode(void)*/
/*���ܣ����ݽ�������*/
/****************************************************************************************************/
void SetRX_Mode(void)
{
   CE=0;
   SPI_RW_Reg(WRITE_REG + CONFIG,0x0f);// IRQ�շ�����ж���Ӧ��16λCRC	��������
   CE=1;
  delay1ms(530);//ע����ʱ����̫�̣������޷���������   
}
/******************************************************************************************************/
/*������unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)*/
/*���ܣ����ݶ�ȡ�����rx_buf���ջ�������*/
/******************************************************************************************************/
uchar nRF24L01_RxPacket(uchar* rx_buf)
{
    uchar revale = 0;

	SetRX_Mode();//����Ϊ����ģʽ

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
/*������void nRF24L01_TxPacket(char * tx_buf)*/
/*���ܣ����� tx_buf������*/
/**********************************************************************************************************/

//���ͳ�����ʱ����
void nRF24L01_TxPacket(uchar * tx_buf)
{
     CE=0;	//ֹͣ��Ƶ����
    SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,TX_ADDRESS,TX_ADR_WIDTH);  //д���ص�ַ
    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);//װ�ؽ��ܵ�ַ 
    SPI_Write_Buf(WR_TX_PLOAD,tx_buf,TX_PLOAD_WIDTH);			  //ת��Ҫ���͵�����
    SPI_RW_Reg(WRITE_REG+CONFIG,0x0e);	 //IRQ�շ��ж���Ӧ��16λCRC,����ģʽ
    CE=1;	 //�ø�CE���������ݷ���
    delay1ms(130);//ע����ʱ����̫�̣������޷���������
}

/****************************************************************************************/
/*NRF24L01��ʼ��*/
/***************************************************************************************/
void init_NRF24L01(void)
{
     CE=0; //ce��0��Ƶ��·ֹͣ����
     CSN=1;//CSN ��1����ָֹ�����
     SCK=0;// ��ֹ��д�Ĵ���
	 IRQ=1;	//�жϸ�λ���ȴ������ж��ź�

    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);//д���ص�ַ 
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);//д���ն˵�ַ,���Ҫ���ñ��Ƶ������RX_ADDR_P0����

  /*  SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);//Ƶ��0�Զ�	ACKӦ������
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);//������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21 */

	 SPI_RW_Reg(WRITE_REG + EN_AA, 0x00);//Ƶ��0�Զ�	ACKӦ���ֹ
	 SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);//������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21 

//	 SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x00);//��ֹ�Զ�����
 
     SPI_RW_Reg(WRITE_REG + RF_CH, 0);//   �����ŵ�����Ϊ2.4GHZ���շ�����һ��
     SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);//���ý������ݳ��ȣ���������Ϊ32�ֽ�
     SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB

//    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);// IRQ�շ�����ж���Ӧ��16λCRC��������}

    CE=1;	 //�ø�CE���������ݷ���
    delay1ms(500);
}





