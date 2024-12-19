#ifndef __IIC_H
#define __IIC_H
#define uchar unsigned char
#define uint unsigned int
#define DELAY_TIME	10
static void I2C_Delay(unsigned char n);
void I2CStart();
void I2CStop();
void I2CSendByte(unsigned char byt);
unsigned char I2CReceiveByte();
unsigned char I2CWaitAck();
void I2CSendAck(unsigned char ackbit);
void ATC24C02_WriteBuffer(uchar *buf,uchar addr,uchar num);
void ATC24C02_ReadBuffer(uchar *buf,uchar addr,uchar num);
#endif