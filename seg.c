#include <STC15F2K60S2.H>
#define uchar unsigned char
#define uint unsigned int
void P0_Out(uchar addr,uchar dat){//P0输出
	P0=dat;
	P2|=addr<<5;
	P2&=0x1f;
}
void Close_Peripheral(){//关闭外设
	P2&=0X1F;
	P0_Out(4,0xff);
	P0_Out(5,0);
}
void Uln_Ctrl(uchar uln){//控制继电器：1开，0关。
	P0_Out(5,uln);
}
void LED_Disp(uchar led){//控制LED:1开，0关，0xff是全开
	P0_Out(4,~led);
}
void Seg_Tran(uchar *seg_char,uchar *seg_code){//数码管转换函数
	uchar i,j,temp;
	for(i=0,j=0;i<8;i++,j++){
		switch(seg_char[j]){
			case '0':temp=0xc0;break;
			case '1':temp=0xf9;break;
			case '2':temp=0xa4;break;
			case '3':temp=0xb0;break;
			case '4':temp=0x99;break;
			case '5':temp=0x92;break;
			case '6':temp=0x82;break;
			case '7':temp=0xf8;break;
			case '8':temp=0x80;break;
			case '9':temp=0x90;break;
			case 'A':
			case 'a':temp=0x88;break;
			case 'B':
			case 'b':temp=0x83;break;
			case 'C':
			case 'c':temp=0xc6;break;
			case 'D':
			case 'd':temp=0xa1;break;
			case 'E':
			case 'e':temp=0x86;break;
			case 'F':
			case 'f':temp=0x8e;break;
			case '-':temp=0xbf;break;
			case ' ':
			default :temp=0xff;break;
		}
		if(seg_char[j+1]=='.'){
			temp=temp&0x7f;
			j++;
		}
		seg_code[i]=temp;
	}
}
void seg_disp(uchar seg_code,uchar seg_pos){//数码管展示
	P0_Out(7,0xff);//段选，消影
	P0_Out(6,1<<seg_pos);//位选
	P0_Out(7,seg_code);
}
