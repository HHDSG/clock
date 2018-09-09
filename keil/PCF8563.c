#include<iic.h>
#include<PCF8563.h>

void time_init()
{
	iic_send_add_byte(0x02,0x00);	//0��
	iic_send_add_byte(0x03,0x00);	//0����    
	iic_send_add_byte(0x04,0x00);	//0Сʱ   
	iic_send_add_byte(0x05,0x01);	//1��
	iic_send_add_byte(0x06,0x08);	//����
	iic_send_add_byte(0x07,0x08);	//8�� 
	iic_send_add_byte(0x08,0x18);	//2018��
}

void pcf_init()
{
    iic_send_add_byte(0x00,0x00);  //����ʱ��
}

//----------------BCDת10����-----------
uchar bcd_dec(uchar bat)
{
	uchar temp1,temp2,tol;
	temp1=bat&0x0f;
	temp2=(bat&0xf0)>>4;
	tol=temp2*10+temp1;
	return tol; 
}