#include<iic.h>
#include<STC12C54.h>
#define uchar unsigned char
#define uint unsigned int 

sbit SDA=P3^0;   //SDA口设置
sbit SCL=P3^1;   //SCL口设置

void delay()    //略微延时  
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
void iic_start()   //启动信号
{
    SDA=1;
    SCL=1;
    delay();
    SDA=0;
    delay();
    SCL=0;
}

void iic_stop()  //停止信号
{
    SDA=0;
    SCL=1;
    delay();
    SDA=1;
    delay();
    SCL=0;
}

void iic_ack()   //应答信号
{
    uchar i=0;
    SCL=1;
    delay();
    while((SDA==1)&&(i<255))
        i++;
    SCL=0;
    delay();
}

void iic_send_byte(uchar bat)  //发送数据
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

uchar iic_rev()  //接受数据
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

void iic_send_add_byte(uchar add,uchar bat) //向某个地址发送某数据
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

uchar iic_rec_add_byte(uchar add) //从某个地址读出数据
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