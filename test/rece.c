// Define SPI pins
#include <reg51.h>
#include <string.h>

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

/***************************************************/
#define TX_ADR_WIDTH   5  // 5�ֽڿ�ȵķ���/���յ�ַ
#define TX_PLOAD_WIDTH 4  // ����ͨ����Ч���ݿ��

sbit LED = P2^1;

uchar code TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  // ����һ����̬���͵�ַ
uchar RX_BUF[TX_PLOAD_WIDTH];
uchar TX_BUF[TX_PLOAD_WIDTH];
uchar flag;
uchar DATA = 0x01;
uchar bdata sta;
sbit  RX_DR     = sta^6;
sbit  TX_DS     = sta^5;
sbit  MAX_RT = sta^4;

sbit CE =  P1^5;
sbit CSN=  P1^4;
sbit SCK=  P1^3;
sbit MOSI= P1^2;
sbit MISO= P1^1;
sbit IRQ = P1^0;

// SPI(nRF24L01) commands
#define READ_REG    0x00  // Define read command to register
#define WRITE_REG   0x20  // Define write command to register
#define RD_RX_PLOAD 0x61  // Define RX payload register address
#define WR_TX_PLOAD 0xA0  // Define TX payload register address
#define FLUSH_TX    0xE1  // Define flush TX register command
#define FLUSH_RX    0xE2  // Define flush RX register command
#define REUSE_TX_PL 0xE3  // Define reuse TX payload register command
#define NOP         0xFF  // Define No Operation, might be used to read status register

// SPI(nRF24L01) registers(addresses)
#define CONFIG      0x00  // 'Config' register address
#define EN_AA       0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR   0x02  // 'Enabled RX addresses' register address
#define SETUP_AW    0x03  // 'Setup address width' register address
#define SETUP_RETR  0x04  // 'Setup Auto. Retrans' register address
#define RF_CH       0x05  // 'RF channel' register address
#define RF_SETUP    0x06  // 'RF setup' register address
#define STATUS      0x07  // 'Status' register address
#define OBSERVE_TX  0x08  // 'Observe TX' register address
#define CD          0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0  0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1  0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2  0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3  0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4  0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5  0x0F  // 'RX address pipe5' register address
#define TX_ADDR     0x10  // 'TX address' register address
#define RX_PW_P0    0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1    0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2    0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3    0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4    0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5    0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17  // 'FIFO Status Register' register address

//--����SPIҪʹ�õ� IO--//
sbit MOSIO = P3^4;
sbit R_CLK = P3^5;
sbit S_CLK = P3^6;

void blink(char i);
//--ȫ�ֺ�������--//

/**************************************************
����: init_io()

����:
    ��ʼ��IO
/**************************************************/
void init_io(void)
{
    CE  = 0;        // ����
    CSN = 1;        // SPI��ֹ
    SCK = 0;        // SPIʱ���õ�
    IRQ = 1;        // �жϸ�λ
    LED = 1;        // �ر�ָʾ��
}
/**************************************************/

/**************************************************
������delay_ms()

������
    �ӳ�x����
/**************************************************/
void delay_ms(uchar x)
{
    uchar i, j;
    i = 0;
    for(i=0; i<x; i++)
    {
       j = 250;
       while(--j);
       j = 250;
       while(--j);
    }
}
/**************************************************/

/**************************************************
������SPI_RW()

������
    ����SPIЭ�飬дһ�ֽ����ݵ�nRF24L01��ͬʱ��nRF24L01
    ����һ�ֽ�
/**************************************************/
uchar SPI_RW(uchar byte)
{
    uchar i;
       for(i=0; i<8; i++)          // ѭ��8��
       {
           MOSI = (byte & 0x80);   // byte���λ�����MOSI
           byte <<= 1;             // ��һλ��λ�����λ
           SCK = 1;                // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
           byte |= MISO;           // ��MISO��byte���λ
           SCK = 0;                // SCK�õ�
       }
    return(byte);               // ���ض�����һ�ֽ�
}
/**************************************************/

/**************************************************
������SPI_RW_Reg()

������
    д����value��reg�Ĵ���
/**************************************************/
uchar SPI_RW_Reg(uchar reg, uchar value)
{
    uchar status;
      CSN = 0;                   // CSN�õͣ���ʼ��������
      status = SPI_RW(reg);      // ѡ��Ĵ�����ͬʱ����״̬��
      SPI_RW(value);             // Ȼ��д���ݵ��üĴ���
      CSN = 1;                   // CSN���ߣ��������ݴ���
      return(status);            // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������SPI_Read()

������
    ��reg�Ĵ�����һ�ֽ�
/**************************************************/
uchar SPI_Read(uchar reg)
{

    uchar reg_val;
      //blink(4);
    CSN = 0;                    // CSN�õͣ���ʼ��������
      SPI_RW(reg);                // ѡ��Ĵ���
      reg_val = SPI_RW(0);        // Ȼ��ӸüĴ���������
    //delay_ms(200);
      CSN = 1;                    // CSN���ߣ��������ݴ���
      return(reg_val);            // ���ؼĴ�������
}
/**************************************************/

/**************************************************
������SPI_Read_Buf()

������
    ��reg�Ĵ�������bytes���ֽڣ�ͨ��������ȡ����ͨ��
    ���ݻ����/���͵�ַ
/**************************************************/
uchar SPI_Read_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
    uchar status, i;
      CSN = 0;                    // CSN�õͣ���ʼ��������
      status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
      for(i=0; i<bytes; i++)
        pBuf[i] = SPI_RW(0);    // ����ֽڴ�nRF24L01����
      CSN = 1;                    // CSN���ߣ��������ݴ���
      return(status);             // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������SPI_Write_Buf()

������
    ��pBuf�����е�����д�뵽nRF24L01��ͨ������д�뷢
    ��ͨ�����ݻ����/���͵�ַ
/**************************************************/
uchar SPI_Write_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
    uchar status, i;
      CSN = 0;                    // CSN�õͣ���ʼ��������
      status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
      for(i=0; i<bytes; i++)
        SPI_RW(pBuf[i]);        // ����ֽ�д��nRF24L01
      CSN = 1;                    // CSN���ߣ��������ݴ���
      return(status);             // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������RX_Mode()

������
    �����������nRF24L01Ϊ����ģʽ���ȴ����շ����豸�����ݰ�
/**************************************************/
void RX_Mode(void)
{
    CE = 0;
      SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
      SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
      SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);           // ʹ�ܽ���ͨ��0
      SPI_RW_Reg(WRITE_REG + RF_CH, 40);                 // ѡ����Ƶͨ��0x40
      SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
      SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
      SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);              // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
    delay_ms(150);
      CE = 1;                                            // ����CE���������豸
}
/**************************************************/

/**************************************************
������TX_Mode()

������
    �����������nRF24L01Ϊ����ģʽ����CE=1��������10us����
    130us���������䣬���ݷ��ͽ����󣬷���ģ���Զ�ת�����
    ģʽ�ȴ�Ӧ���źš�
/**************************************************/
void TX_Mode(uchar * BUF)
{
    CE = 0;
      SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // д�뷢�͵�ַ
      SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
      SPI_Write_Buf(WR_TX_PLOAD, BUF, TX_PLOAD_WIDTH);                  // д���ݰ���TX FIFO
      SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
      SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);   // ʹ�ܽ���ͨ��0
      SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
      SPI_RW_Reg(WRITE_REG + RF_CH, 40);         // ѡ����Ƶͨ��0x40
      SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
      SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�
    delay_ms(150);
    CE = 1;
}
/**************************************************/

/**************************************************
������Check_ACK()

������
    �������豸���޽��յ����ݰ����趨û���յ�Ӧ����
    ���Ƿ��ط�
/**************************************************/
uchar Check_ACK(bit clear)
{
    while(IRQ);
    sta = SPI_RW(NOP);                    // ����״̬�Ĵ���
    if(TX_DS)
    {
        //blink(3);
    }
    //blink(5);
    if(MAX_RT)
        if(clear)                         // �Ƿ����TX FIFO��û������ڸ�λMAX_RT�жϱ�־���ط�
            SPI_RW(FLUSH_TX);
    SPI_RW_Reg(WRITE_REG + STATUS, sta);  // ���TX_DS��MAX_RT�жϱ�־
    IRQ = 1;
    if(TX_DS)
        return(0x00);
    else
        return(0xff);
}
/**************************************************/

/**************************************************
������CheckButtons()

������
    ��鰴���Ƿ��£���������һ�ֽ�����
/**************************************************/
void CheckButtons()
{
    P3 |= 0x00;
    if(!(P3 & 0x01))                    // ��ȡP3^0״̬
    {
        delay_ms(20);
        if(!(P3 & 0x01))                // ��ȡP3^0״̬
        {
            TX_BUF[0] = ~DATA;          // �����͵�����
            //TX_BUF[0] = 0xff;          // �����͵�����
            TX_Mode(TX_BUF);            // ��nRF24L01����Ϊ����ģʽ����������            
            //LED = ~DATA;                // �����͵�LED��ʾ
            Check_ACK(0);               // �ȴ�������ϣ����TX FIFO
            delay_ms(250);
            delay_ms(250);
            LED = 1;                    // �ر�LED
            RX_Mode();                    // ����Ϊ����ģʽS
            while(!(P3 & 0x01));
            DATA <<= 1;
            if(!DATA)
                DATA = 0x01;
        }
    }
}
/**************************************************/

void blink(char i)
{
    while(i--)
    {
        LED = 1;
        delay_ms(500);
        LED = 0;
        delay_ms(500);
    }

}

/**************************************************
������main()

������
    ������
/**************************************************/
void main(void)
{
    init_io();                      // ��ʼ��IO
    RX_Mode();                      // ����Ϊ����ģʽ

    while(1)
    {
        sta = SPI_Read(STATUS);      // ��״̬�Ĵ���
        //delay_ms(200);
        if(RX_DR)                  // �ж��Ƿ���ܵ�����
        {
            SPI_Read_Buf(RD_RX_PLOAD, RX_BUF, TX_PLOAD_WIDTH);  // ��RX FIFO��������
            flag = 1;
        }
        SPI_RW_Reg(WRITE_REG + STATUS, sta);  // ���RX_DS�жϱ�־

        if(flag)                   // �������
        {
            if(RX_BUF[0] == 1)
            {
                blink(2);
            }

            if(RX_BUF[0] == 2)
            {
                blink(4);
            }
            flag = 0;               // ���־
            delay_ms(250);
            delay_ms(250);
            LED = 1;               // �ر�LED
        }
    }
}