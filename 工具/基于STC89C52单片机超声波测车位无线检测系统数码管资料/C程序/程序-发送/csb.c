#include<reg52.h>								
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int
///////////////////////////////////////////////////////
bit      flag =0;
unsigned int  time=0;
unsigned int  timer=0;

bit flag_sb;				 //�Ƿ�ز�
unsigned char key_num=0;
unsigned char bijiao_flag=0;
unsigned char car_num=0;	//��λ��ֵ					 
unsigned char Set_car_H=4;  //���ó�����ֵ
signed char   s_car_num=0;	//ʣ�೵λ��ֵ	

uchar flag1,flag2;	  //���� 2 ����־λ
uchar flag3,flag4;	  //���� 2 ����־λ
uchar flag5,flag6;	  //���� 2 ����־λ
uchar flag7,flag8;	  //���� 2 ����־λ

uchar N1=0,N11=0;		//�г�����û�б�־
uchar N2=0,N22=0;
uchar N3=0,N33=0;
uchar N4=0,N44=0;      
               
uint wei_x=20;				 //��ȫ����

uchar flag_monden=0;    //ģʽ
uchar baojing_moden=0;

uchar key_flag=1;
unsigned int S11=0;
void Shumaguan(uint num);
void Conut(void);

#include "shumaguan.h"
#include "NRF24l01.h"
//#include "eeprom.h"


void delay_ms(uint z)
{
	uint a,b;
	for(a=z;z>0;z--)
	for(b=50;b>0;b--);	
}
void Conut(void)
{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;	
	 S=(time*1.87)/100;     //�������CM
	 if((S>=500)||flag==1) //����������Χ
	 {	 
	 	   flag=0;
		   S=888;
	 }

}

////////////////////////////////////////////////////////////////////////////////////////////////////
 void campare_display()	//�Ƚ� 						  �ĸ���λ�Ƿ���λ���� 
{
 
		   if((N1==1)||(N2==1)||(N3==1)||(N4==1)) {
			       if(N1==1){
				     	   left_up_red=0; 
						   TxBuf[5]='A'; 						   
					  }
			        else{
					       left_up_red=1; 
						   TxBuf[5]=0;	
					}
					if(N2==1){

						   left_down_red=0; 
						   TxBuf[6]='B';
							
					} else{
							left_down_red=1;
							TxBuf[6]=0;	
					}
/////////////////////////////////////////////////////////////
					if(N3==1){
						   right_down_red =0; 
							TxBuf[7]='C';	
					} else{
                           right_down_red =1; 
							TxBuf[7]=0;	
					}
					if(N4==1){
							right_up_red =0; 
							TxBuf[8]='D';		
					} else{
						   right_up_red =1; 
							TxBuf[8]=0;
					}
						
			  }	 else{
//						Lcd_ShowSring(1,0,"     ");
                       left_down_red=1;left_up_red=1;  
					   right_down_red =1; right_up_red =1;  
					
				}
									
}
void  check_car()	  //ͳ�Ƴ�λ������
{

	if(S2<wei_x)				// С��20cm
		{
			
		  flag1=1; //��־λflag1		     	
	     if(flag1==1)//  flag1=1 ������A ˵���г�
		  {
				   delay_ms(5);
					if(N1==0){						
					  car_num++;	 //��λ��ֵ��1
					  N1=1;
					 }					  //
					flag1=0;	  //���־λ
					flag2=1;	  //������־
					N11=0;
			}	
		} 
		 else{		 //�����ⲻ����

			  if(N11==0){						
						 car_num--;		//��λ��ֵ��1
						 TxBuf[5]=0;
						  N11=1;
					 }
		      
			       N1=0;
			}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	    if(S1<wei_x)				// С��20cm
		{

		  flag3=1; ////��־λflag3
			
		  if(flag3==1)//  ������B  ����Թܼ�⵽ ˵���г�
		  {
				    delay_ms(5);
					if(N2==0){						
					  car_num++;	  	 //��λ��ֵ��1
					  N2=1;
					 }					 
					flag3=0;	  //��ձ�־λ
					flag4=1;	   //������־
					N22=0;
				
		 }
	    }	
	     
		else {		 //�����ⲻ����

			  if(N22==0){						
						 car_num--;		 	//��λ��ֵ��1
						 TxBuf[6]=0;
						  N22=1;
					 }
		      
			       N2=0;
			}	
/////////////////////////////////////////////////////////////////////////////////////////////B����	
		  if(S3<wei_x)
		  {
			flag5=1; ////��־λflag5
		  if(flag5==1)//  ������C	����Թܼ�⵽ ˵���г�
		    {
				    delay_ms(5);
					if(N3==0){						
					  car_num++;	  	 //��λ��ֵ��1
					  N3=1;
					 }					  //
					flag5=0;	  //��ձ�־λ
					flag6=1;	  //������־
					N33=0;
				
		   }
     	}
		
	     
		 else {		  //�����ⲻ����

			  if(N33==0){						
						 car_num--;
						 TxBuf[7]=0;	//��λ��ֵ��1
						  N33=1;
					 }
		      
			       N3=0;
			}	
///////////////////////////////////////////////////////////////////////////////////////////////
	  	if(S4<wei_x)
		  {
			flag7=1; ////��־λflag5
		  if(flag7==1)//  ������C	����Թܼ�⵽ ˵���г�
		    {
				    delay_ms(5);
					if(N4==0){						
					  car_num++;	  	 //��λ��ֵ��1
					  N4=1;
					 }					  //
					flag7=0;	  //��ձ�־λ
					flag8=1;	  //������־
					N44=0;
				
		   }
     	}
		
	     
		 else {		  //�����ⲻ����

			  if(N44==0){						
						 car_num--;
						 TxBuf[8]=0;	//��λ��ֵ��1
						  N44=1;
					 }
		      
			       N4=0;
			}


		
}
///////////////////////////////////////////////////////////////
//������    
 void main()
{		  
            uchar num;
//			read_eeprom();	 //������������	  
		    init_NRF24L01(); //��ʼ������
 			init();
			TIM2Inital();
			TxBuf[0]=1;	  //ģ��			   ����
		 	while(1)
			{ 	
			     ////////////////////////////////////////////////////////////////
	   			if(Set_car_H>=car_num){	 //���õĳ�λ�����ڳ���	
						    s_car_num=Set_car_H-car_num;		//ʣ�೵λ
										
						  }  
			    TxBuf[1]=car_num/10;//ʮλ
  		        TxBuf[2]=car_num%10;//��λ 
				TxBuf[3]=s_car_num/10;//ʮλ
  		        TxBuf[4]=s_car_num%10;//��λ

				num++;
				if(num==2){		 //ģ��
				num=0;
	 			nRF24L01_TxPacket(TxBuf);
		        }
		        SPI_RW_Reg(WRITE_REG+STATUS,0XFF);//������ա��������ݣ�����ط��жϣ�RX_FIFO��TX_FIFO�Ĵ������
			  
			      if(flag_monden==0)
				  {		 	
 			   
	

				  }
				   campare_display();
				   check_car();
				   display(&count_flag);	 //��ʾ
				   //Shumaguan(Set_car_H);
				 // fenjie(data_num,s_car_num);
				  jisuan(Set_car_H,s_car_num);
			 }
 }

