#include <STC15F2K60S2.H>
#define uchar unsigned char
#define uint unsigned int
void key_read(uchar *pkey_valu){//按键检测函数，没有消抖
	uint key_code;
	uchar key_valu;	
	P44=0;P42=P35=P34=1;
	key_code=P3;
	P44=1;P42=0;
	key_code=(key_code<<4)|(P3&0X0F);
	P42=1;P35=0;
	key_code=(key_code<<4)|(P3&0X0F);
	P35=1;P34=0;
	key_code=(key_code<<4)|(P3&0X0F);
	switch(~key_code){
		case 0x8000:key_valu=4;break;//s4
		case 0x4000:key_valu=5;break;//s5
		case 0x2000:key_valu=6;break;//s6
		case 0x1000:key_valu=7;break;//s7
		case 0x0800:key_valu=8;break;//s8
		case 0x0400:key_valu=9;break;//s9
		case 0x0200:key_valu=10;break;//s10
		case 0x0100:key_valu=11;break;//s11
		case 0x0080:key_valu=12;break;//s12
		case 0x0040:key_valu=13;break;//s13
		case 0x0020:key_valu=14;break;//s14
		case 0x0010:key_valu=15;break;//s15
		case 0x0008:key_valu=16;break;//s16
		case 0x0004:key_valu=17;break;//s17
		case 0x0002:key_valu=18;break;//s18
		case 0x0001:key_valu=19;break;//s19
		default: key_valu=0;
	}
	if(key_valu!=pkey_valu[2]){//不同就记录
		pkey_valu[0]=key_valu;//按下键值
		pkey_valu[1]=pkey_valu[2];//松开键值
		pkey_valu[2]=key_valu;//历史键值
	}
	else{//相同就消除
		pkey_valu[0]=0;
		pkey_valu[1]=0;
	}
}