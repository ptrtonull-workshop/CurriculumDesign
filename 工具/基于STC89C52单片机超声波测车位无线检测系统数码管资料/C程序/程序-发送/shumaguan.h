
sbit wei4  =P2^7;	 //����ܵ�λѡ4
sbit wei3  =P2^6;	 //����ܵ�λѡ3
sbit wei2  =P2^5;	 //����ܵ�λѡ2
sbit wei1  =P2^4;	 //����ܵ�λѡ1

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
                0xFF,  //Ϩ��
                0xFF  //�Զ���
 
                         };

 
//�жϳ�ʼ��
  void init()
  {	  
  	TMOD=0x11;		//��ʱ��0�Ͷ�ʱ��1���Ƿ�ʽ1,16λ��ʱ�� 
			
	TH0=0;
	TL0=0;          
	TH1=0xf8;		   //2MS��ʱ
	TL1=0x30;

	ET0=1;             //����T0�ж�
	ET1=1;			   //����T1�ж�
	TR1=1;			   //������ʱ��
	EA=1;			   //�������ж�
  }
/********************************************************/
void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
  {
    flag=1;							 //�ж������־
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
	  TX=1;			                //200MS  ����һ��ģ��
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
	  
void TIM2Inital()	   //��ʱ��2�ĳ�ʼ��

{

  RCAP2H = (65536-1100)/256;//@ 16bit �Զ�����
  RCAP2L = (65536-1100)%256;
  ET2=1;
  EA=1;
  TR2=1;  //��ʱ��2

}
unsigned char num33=0; 
unsigned char count1=0; 
void time2()interrupt 5		//��ʱ��2 ����
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
				            while(!RX1);		 //��RXΪ��ʱ�ȴ�
							TR0=1;			    //��������
							while(RX1);			//��RXΪ1�������ȴ�
							TR0=0;				//�رռ���
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
				            while(!RX2);		 //��RXΪ��ʱ�ȴ�
							TR0=1;			    //��������
							while(RX2);			//��RXΪ1�������ȴ�
							TR0=0;				//�رռ���
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
				            while(!RX3);		 //��RXΪ��ʱ�ȴ�
							TR0=1;			    //��������
							while(RX3);			//��RXΪ1�������ȴ�
							TR0=0;				//�رռ���
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
						    while(!RX4);		 //��RXΪ��ʱ�ȴ�
							TR0=1;			    //��������
							while(RX4);			//��RXΪ1�������ȴ�
							TR0=0;				//�رռ���
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
