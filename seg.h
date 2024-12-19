#ifndef __SEG_H
#define __SEG_H
#define uchar unsigned char
#define uint unsigned int
void P0_Out(uchar addr,uchar dat);//P0输出
void LED_Disp(unsigned char led);
void Close_Peripheral();//关闭外设
void Uln_Ctrl(uchar uln);//控制继电器：1开，0关。
void LED_Disp(uchar led);//控制LED:1开，0关，0xff是全开
void Seg_Tran(uchar *seg_char,uchar *seg_code);//数码管转换函数
void seg_disp(uchar seg_code,uchar seg_pos);//数码管展示
#endif