#include<reg52.h>								
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int
///////////////////////////////////////////////////////
bit      flag =0;
unsigned int  time=0;
unsigned int  timer=0;

bit flag_sb;				 //是否回波
unsigned char key_num=0;
unsigned char bijiao_flag=0;
unsigned char car_num=0;	//车位数值					 
unsigned char Set_car_H=4;  //设置车数数值
signed char   s_car_num=0;	//剩余车位数值	

uchar flag1,flag2;	  //设置 2 个标志位
uchar flag3,flag4;	  //设置 2 个标志位
uchar flag5,flag6;	  //设置 2 个标志位
uchar flag7,flag8;	  //设置 2 个标志位

uchar N1=0,N11=0;		//有车或者没有标志
uchar N2=0,N22=0;
uchar N3=0,N33=0;
uchar N4=0,N44=0;      
               
uint wei_x=20;				 //安全距离

uchar flag_monden=0;    //模式
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
	 S=(time*1.87)/100;     //算出来是CM
	 if((S>=500)||flag==1) //超出测量范围
	 {	 
	 	   flag=0;
		   S=888;
	 }

}

////////////////////////////////////////////////////////////////////////////////////////////////////
 void campare_display()	//比较 						  四个车位是否在位置上 
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
void  check_car()	  //统计车位数函数
{

	if(S2<wei_x)				// 小于20cm
		{
			
		  flag1=1; //标志位flag1		     	
	     if(flag1==1)//  flag1=1 传感器A 说明有车
		  {
				   delay_ms(5);
					if(N1==0){						
					  car_num++;	 //车位数值加1
					  N1=1;
					 }					  //
					flag1=0;	  //清标志位
					flag2=1;	  //启动标志
					N11=0;
			}	
		} 
		 else{		 //否则检测不到车

			  if(N11==0){						
						 car_num--;		//车位数值减1
						 TxBuf[5]=0;
						  N11=1;
					 }
		      
			       N1=0;
			}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	    if(S1<wei_x)				// 小于20cm
		{

		  flag3=1; ////标志位flag3
			
		  if(flag3==1)//  传感器B  红外对管检测到 说明有车
		  {
				    delay_ms(5);
					if(N2==0){						
					  car_num++;	  	 //车位数值加1
					  N2=1;
					 }					 
					flag3=0;	  //清空标志位
					flag4=1;	   //启动标志
					N22=0;
				
		 }
	    }	
	     
		else {		 //否则检测不到车

			  if(N22==0){						
						 car_num--;		 	//车位数值减1
						 TxBuf[6]=0;
						  N22=1;
					 }
		      
			       N2=0;
			}	
/////////////////////////////////////////////////////////////////////////////////////////////B区域	
		  if(S3<wei_x)
		  {
			flag5=1; ////标志位flag5
		  if(flag5==1)//  传感器C	红外对管检测到 说明有车
		    {
				    delay_ms(5);
					if(N3==0){						
					  car_num++;	  	 //车位数值加1
					  N3=1;
					 }					  //
					flag5=0;	  //清空标志位
					flag6=1;	  //启动标志
					N33=0;
				
		   }
     	}
		
	     
		 else {		  //否则检测不到车

			  if(N33==0){						
						 car_num--;
						 TxBuf[7]=0;	//车位数值减1
						  N33=1;
					 }
		      
			       N3=0;
			}	
///////////////////////////////////////////////////////////////////////////////////////////////
	  	if(S4<wei_x)
		  {
			flag7=1; ////标志位flag5
		  if(flag7==1)//  传感器C	红外对管检测到 说明有车
		    {
				    delay_ms(5);
					if(N4==0){						
					  car_num++;	  	 //车位数值加1
					  N4=1;
					 }					  //
					flag7=0;	  //清空标志位
					flag8=1;	  //启动标志
					N44=0;
				
		   }
     	}
		
	     
		 else {		  //否则检测不到车

			  if(N44==0){						
						 car_num--;
						 TxBuf[8]=0;	//车位数值减1
						  N44=1;
					 }
		      
			       N4=0;
			}


		
}
///////////////////////////////////////////////////////////////
//主函数    
 void main()
{		  
            uchar num;
//			read_eeprom();	 //读出保存数据	  
		    init_NRF24L01(); //初始化无线
 			init();
			TIM2Inital();
			TxBuf[0]=1;	  //模块			   发送
		 	while(1)
			{ 	
			     ////////////////////////////////////////////////////////////////
	   			if(Set_car_H>=car_num){	 //设置的车位数大于车数	
						    s_car_num=Set_car_H-car_num;		//剩余车位
										
						  }  
			    TxBuf[1]=car_num/10;//十位
  		        TxBuf[2]=car_num%10;//个位 
				TxBuf[3]=s_car_num/10;//十位
  		        TxBuf[4]=s_car_num%10;//个位

				num++;
				if(num==2){		 //模块
				num=0;
	 			nRF24L01_TxPacket(TxBuf);
		        }
		        SPI_RW_Reg(WRITE_REG+STATUS,0XFF);//清除接收、发送数据，最多重发中断；RX_FIFO、TX_FIFO寄存器清空
			  
			      if(flag_monden==0)
				  {		 	
 			   
	

				  }
				   campare_display();
				   check_car();
				   display(&count_flag);	 //显示
				   //Shumaguan(Set_car_H);
				 // fenjie(data_num,s_car_num);
				  jisuan(Set_car_H,s_car_num);
			 }
 }

