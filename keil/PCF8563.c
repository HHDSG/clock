#include<iic.h>
#include<PCF8563.h>

void time_init()
{
	iic_send_add_byte(0x02,0x00);	//0秒
	iic_send_add_byte(0x03,0x00);	//0分钟    
	iic_send_add_byte(0x04,0x00);	//0小时   
	iic_send_add_byte(0x05,0x01);	//1号
	iic_send_add_byte(0x06,0x08);	//星期
	iic_send_add_byte(0x07,0x08);	//8月 
	iic_send_add_byte(0x08,0x18);	//2018年
}

void pcf_init()
{
    iic_send_add_byte(0x00,0x00);  //启动时钟
}

//----------------BCD转10进制-----------
uchar bcd_dec(uchar bat)
{
	uchar temp1,temp2,tol;
	temp1=bat&0x0f;
	temp2=(bat&0xf0)>>4;
	tol=temp2*10+temp1;
	return tol; 
}