#ifndef IIC_H
#define IIC_H

#include<STC12C54.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int 



void delay();    //��΢��ʱ
void delayNus(int n);

void iic_start();   //�����ź�

void iic_stop();  //ֹͣ�ź�

void iic_ack();   //Ӧ���ź�

void iic_send_byte(uchar bat);  //��������

uchar iic_rev();  //��������

void iic_send_add_byte(uchar add,uchar bat); //��ĳ����ַ����ĳ����

uchar iic_rec_add_byte(uchar add); //��ĳ����ַ��������

#endif