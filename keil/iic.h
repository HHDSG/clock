#ifndef IIC_H
#define IIC_H

#include<STC12C54.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int 



void delay();    //略微延时
void delayNus(int n);

void iic_start();   //启动信号

void iic_stop();  //停止信号

void iic_ack();   //应答信号

void iic_send_byte(uchar bat);  //发送数据

uchar iic_rev();  //接受数据

void iic_send_add_byte(uchar add,uchar bat); //向某个地址发送某数据

uchar iic_rec_add_byte(uchar add); //从某个地址读出数据

#endif