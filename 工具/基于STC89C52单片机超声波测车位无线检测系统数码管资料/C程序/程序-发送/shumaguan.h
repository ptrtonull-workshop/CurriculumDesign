
sbit wei4  =P2^7;	 //数码管的位选4
sbit wei3  =P2^6;	 //数码管的位选3
sbit wei2  =P2^5;	 //数码管的位选2
sbit wei1  =P2^4;	 //数码管的位选1

sbit  RX1 = P3^3;
sbit  RX2 = P3^4;
sbit  RX3 = P3^5;
sbit  RX4 = P3^6;

sbit  TX = P3^7;

sbit  left_up_red    = P1^7;
sbit  left_down_red  = P1^6;
sbit  right_up_red   = P2^1;
sbit  right_down_red = P2^0;


unsigned int S=0,S1=0,S2=0,S3=0,S4=0;
unsigned int SET_H_U=100,SET_H_D=100,SET_H_L=100,SET_H_R=100;

uchar    L_BAOJING =0,U_BAOJING =0,R_BAOJING =0,D_BAOJING =0;
unsigned char count_flag=0; 

sbit DP=P0^7;
bit moshi=0;
unsigned char idata data_num[4]={8,8,8,8};
unsigned char count; 
bit flag_300ms ;
void fenjie(unsigned char *p,unsigned int num1);

unsigned char code  leddata[]={ 
 
                0xC0,  //"0"
                0xF9,  //"1"
                0xA4,  //"2"
                0xB0,  //"3"
                0x99,  //"4"
                0x92,  //"5"
                0x82,  //"6"
                0xF8,  //"7"
                0x80,  //"8"
                0x90,  //"9"
                0x88,  //"A"
                0x83,  //"B"
                0xC6,  //"C"
                0xA1,  //"D"
                0x86,  //"E"
                0x8E,  //"F"
                0x89,  //"H"
                0xC7,  //"L"
                0xC8,  //"n"
                0xC1,  //"u"
                0x8C,  //"P"
                0xA3,  //"o"
                0xBF,  //"-"
                0xFF,  //熄灭
                0xFF  //自定义
 
                         };

 
//中断初始化
  void init()
  {	  
  	TMOD=0x11;		//定时器0和定时器1都是方式1,16位定时器 
			
	TH0=0;
	TL0=0;          
	TH1=0xf8;		   //2MS定时
	TL1=0x30;

	ET0=1;             //允许T0中断
	ET1=1;			   //允许T1中断
	TR1=1;			   //开启定时器
	EA=1;			   //开启总中断
  }
/********************************************************/
void zd0() interrupt 1 		 //T0中断用来计数器溢出,超过测距范围
  {
    flag=1;							 //中断溢出标志
  }

/********************************************************/
 void  zd3()  interrupt 3 	
 {
 	
	 TH1=0xf8;
	 TL1=0x30;		   //
	 timer++;
//	 fenjie(data_num,S11);
	 
	 if(timer>=400)
	 {
	  timer=0;
	  TX=1;			                //200MS  启动一次模块
	  _nop_(); _nop_(); _nop_(); 
	  _nop_(); _nop_(); _nop_(); 
	  _nop_(); _nop_(); _nop_(); 
	  _nop_(); _nop_(); _nop_(); 
	  _nop_(); _nop_(); _nop_(); 
	  _nop_(); _nop_(); _nop_(); 
	  _nop_(); _nop_(); _nop_();
	  TX=0;	 
	 }
    
	 
}

unsigned char jieguo[4];

void jisuan(unsigned char t12,unsigned char t34)
{
		jieguo[0]=t12/10%10;
		jieguo[1]=t12%10;
		jieguo[2]=t34/10%10;
		jieguo[3]=t34%10;

}
	  
void TIM2Inital()	   //定时器2的初始化

{

  RCAP2H = (65536-1100)/256;//@ 16bit 自动重载
  RCAP2L = (65536-1100)%256;
  ET2=1;
  EA=1;
  TR2=1;  //定时器2

}
unsigned char num33=0; 
unsigned char count1=0; 
void time2()interrupt 5		//定时器2 服务
 {
	     TF2=0;
		if(moshi==0)
		{
			switch(num33){
			//	case 0:   	wei1=1;	wei2=1;wei3=1;wei4=1;   break;  //	P0= leddata[*data_num];
			//	case 1: 	P0= leddata[*(data_num)];  	    wei1=1;	wei2=1;wei3=1;wei4=1; DP=1;break;
			//	case 2: 	P0= leddata[*(data_num+1)];  	wei1=1;	wei2=1;wei3=0;wei4=1; break;
			//	case 3: 	P0= leddata[*(data_num+2)];  	wei1=1;	wei2=1;wei3=1;wei4=0; break;

		
		  	    case 0: 	P0= leddata[jieguo[0]];  	wei1=0;	wei2=1;wei3=1;wei4=1; break;
			    case 1: 	P0= leddata[jieguo[1]];  	wei1=1;	wei2=0;wei3=1;wei4=1; DP=0; break;
			    case 2: 	P0= leddata[jieguo[2]];  	wei1=1;	wei2=1;wei3=0;wei4=1; break;
			    case 3: 	P0= leddata[jieguo[3]];  	wei1=1;	wei2=1;wei3=1;wei4=0; DP=0;break;
				default : break;
	
			}

			if(num33<3){
			   		num33++;
			}
			else{
			 	 	num33=0;
			}
	   }

   if(count1<2){
		count1++;

	}
	else{
			count1 =0;
			if(count_flag<3) {
				 count_flag++;
			}
			else {
					count_flag=0;
			}

			
	} 
	
 }
///////////////////////////////////////////////////////////////////////////////////////
void display(unsigned char *p)
 {
  
		  
			switch(*p){

				  case 0:  if(RX1==1){S1=0;L_BAOJING=1; break;} 
				            while(!RX1);		 //当RX为零时等待
							TR0=1;			    //开启计数
							while(RX1);			//当RX为1计数并等待
							TR0=0;				//关闭计数
							Conut();
							S1=S;
						//	fenjie(data_num,S1);
			
						//	left_down_red=0; 
						//	left_up_red=1; 
						//	right_up_red=1; 
						//	right_down_red=1;
							L_BAOJING=0; 
							break; 
							
			     case 1:    if(RX2==1){S2=0; U_BAOJING=1;break;} 
				            while(!RX2);		 //当RX为零时等待
							TR0=1;			    //开启计数
							while(RX2);			//当RX为1计数并等待
							TR0=0;				//关闭计数
							Conut();
							S2=S;  
						//	fenjie(data_num,S2); 
					
						//	left_up_red=0; 
						//	left_down_red=1; 
						//	right_up_red=1; 
						//	right_down_red=1;
							U_BAOJING=0;
							 break;
							
							   
				  case 2:  if(RX3==1){S3=0;D_BAOJING=1; break;} 
				            while(!RX3);		 //当RX为零时等待
							TR0=1;			    //开启计数
							while(RX3);			//当RX为1计数并等待
							TR0=0;				//关闭计数
							Conut();
					        S3=S; 
						//	fenjie(data_num,S3); 
						//	left_down_red=1; 
						//	left_up_red=1; 	
															
						//	right_down_red=1;  
						//	right_up_red =0; 
							D_BAOJING=0;							
							break; 
							
			       case 3:  
				            if(RX4==1){	S4=0;R_BAOJING=1; break;} 
						    while(!RX4);		 //当RX为零时等待
							TR0=1;			    //开启计数
							while(RX4);			//当RX为1计数并等待
							TR0=0;				//关闭计数
							Conut();	
							S4=S; 
						//	fenjie(data_num,S4); 
						//	left_down_red=1; 
						//	left_up_red=1;
						//	right_up_red=1;
						//	right_down_red=0; 

							R_BAOJING=0;
							break;

				   default: break;				   
			        }
}
