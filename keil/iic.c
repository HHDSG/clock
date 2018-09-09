#include<iic.h>
#include<STC12C54.h>
#define uchar unsigned char
#define uint unsigned int 

sbit SDA=P3^0;   //SDA������
sbit SCL=P3^1;   //SCL������

void delay()    //��΢��ʱ  
{ 
    int i=0;
    for(i=0;i<10;i++)  //
         _nop_();
}
void delayNus(int n)
{
	int i=0;
    for(i=0;i<n;i++)  //
        delay();
}
void iic_start()   //�����ź�
{
    SDA=1;
    SCL=1;
    delay();
    SDA=0;
    delay();
    SCL=0;
}

void iic_stop()  //ֹͣ�ź�
{
    SDA=0;
    SCL=1;
    delay();
    SDA=1;
    delay();
    SCL=0;
}

void iic_ack()   //Ӧ���ź�
{
    uchar i=0;
    SCL=1;
    delay();
    while((SDA==1)&&(i<255))
        i++;
    SCL=0;
    delay();
}

void iic_send_byte(uchar bat)  //��������
{
    uchar i,temp;
    temp=bat;
    for(i=0;i<=7;i++)
    {
        temp=temp<<1;
        SCL=0;
        SDA=CY;
        delay();
        SCL=1;
        delay();
    }
    SCL=0;
    delay();
    SDA=1;
    delay();
}

uchar iic_rev()  //��������
{
    uchar temp,i;
    SCL=0;
    delay();
    SDA=1;
    for(i=0;i<=7;i++)
    {
        SCL=1;
        delay();
        temp=(temp<<1)|SDA;
        SCL=0;
        delay();
    }
    delay();
    return temp;
}

void iic_send_add_byte(uchar add,uchar bat) //��ĳ����ַ����ĳ����
{
    iic_start();
    iic_send_byte(0xa2);
    iic_ack();
    iic_send_byte(add);
    iic_ack();
    iic_send_byte(bat);
    iic_ack();
    iic_stop();
}

uchar iic_rec_add_byte(uchar add) //��ĳ����ַ��������
{
    uchar temp;
    iic_start();
    iic_send_byte(0xa2);
    iic_ack();
    iic_send_byte(add);
    iic_ack();
    iic_start();
    iic_send_byte(0xa3);
    iic_ack();
    temp=iic_rev();
    iic_stop();
    return temp;
}