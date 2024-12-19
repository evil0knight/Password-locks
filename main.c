#include <STC15F2K60S2.H>
#include "seg.h"
#include "tim.h"
#include <stdio.h>
#include "key.h"
#include "iic.h"
#include <string.h>
#include <intrins.h>
uchar seg_pos=0;
uchar seg_code[8];
uchar seg_char[9];
uint uitms=0;
uchar i=0;//密码锁用
uchar mode=0;//0密码锁模式,1修改密码模式
uchar bufright[9]="12345678";
uchar buftemp[4]={0};
uint uiseg_Dly=0;
uchar ucseg_Dly=0;
uchar key_valu[3];
void Seg_Proc();//数码管显示函数
void Key_proc();//按键检测函数
//////////////////////////////////////////////////////////////////
void panduan();
void Delay1000ms();		//@12.000MHz
//////////////////////////////////////////////////////////////////
void main(){
  Close_Peripheral();
	Timer1Init();
	ATC24C02_ReadBuffer(bufright,0,8);
	while(1){
		Seg_Proc();
		Key_proc();
		panduan();
	}
}
void T0_Proc()interrupt 3{
	uitms++;
	uiseg_Dly++;
	ucseg_Dly++;
}
void Seg_Proc(){//数码管显示函数
	if(uiseg_Dly>500){
		uiseg_Dly=0;
//		sprintf(seg_char,"1.%07u",(uint) num);
		Seg_Tran(seg_char,seg_code);
	}
	if(ucseg_Dly>1){
		ucseg_Dly=0;
		seg_disp(seg_code[seg_pos],seg_pos);
		seg_pos=++seg_pos&7;//数码管循环显示
	}
}
void Key_proc(){//按键检测函数+键值控制函数
	if(uitms<10){
		return;
	}
	uitms=0;
	key_read(key_valu);
	switch(key_valu[0]){
	case 4:seg_char[i++]='0';break;
	case 5:seg_char[i++]='7';break;
	case 6:seg_char[i++]='4';break;
	case 7:seg_char[i++]='1';break;
	case 8:seg_char[--i]='\0';break;
	case 9:seg_char[i++]='8';break;
	case 10:seg_char[i++]='5';break;
	case 11:seg_char[i++]='2';break;
	case 12:mode=1;strcpy(seg_char,"        ");i=0;break;
	case 13:seg_char[i++]='9';break;
	case 14:seg_char[i++]='6';break;
	case 15:seg_char[i++]='3';break;
	case 16:break;
	case 17:break;
	case 18:break;
	case 19:break;
	}
}

//////////////////
void panduan(){
	seg_char[i]='\0';
	if((mode==0)&&(i==8)&&(strcmp(seg_char,bufright)==0)){
		Uln_Ctrl(0x20);
		Delay1000ms();		//@12.000MHz
		Close_Peripheral();
		strcpy(seg_char,"        ");
		i=0;
	}
	else if((mode==0)&&(i==8)&&(strcmp(seg_char,bufright)!=0)){
		Uln_Ctrl(0x40);
		Delay1000ms();		//@12.000MHz
		Close_Peripheral();
		Delay1000ms();		//@12.000MHz
		strcpy(seg_char,"        ");
		i=0;
	}
	else if((mode==1)&&(i==8)&&(strcmp(seg_char,bufright)==0)){
		LED_Disp(0xff);
		Delay1000ms();		//@12.000MHz
		Close_Peripheral();
		strcpy(seg_char,"        ");
		i=0;
		mode=2;
	}
	else if((mode==1)&&(i==8)&&(strcmp(seg_char,bufright)!=0)){
		LED_Disp(0x0f);
		Delay1000ms();		//@12.000MHz
		Close_Peripheral();
		strcpy(seg_char,"        ");
		i=0;
		mode=0;
	}
	else if((mode==2)&&(i==8)){
		LED_Disp(0xf0);
		Delay1000ms();		//@12.000MHz
		Close_Peripheral();
		mode=0;
		strcpy(bufright,seg_char);
		ATC24C02_WriteBuffer(seg_char,0,8);
		ATC24C02_ReadBuffer(bufright,0,8);
		strcpy(seg_char,"        ");
		i=0;
	}
	
}
void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 46;
	j = 153;
	k = 245;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//////////////////
