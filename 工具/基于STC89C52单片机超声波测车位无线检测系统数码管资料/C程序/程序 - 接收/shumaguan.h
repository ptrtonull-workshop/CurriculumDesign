
sbit wei4  =P2^7;	 //����ܵ�λѡ4
sbit wei3  =P2^6;	 //����ܵ�λѡ3
sbit wei2  =P2^5;	 //����ܵ�λѡ2
sbit wei1  =P2^4;	 //����ܵ�λѡ1



sbit DP=P0^7;
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

			switch(num33){
		
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