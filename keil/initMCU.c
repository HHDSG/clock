#include<initMCU.h>
#include<STC12C54.h>
#include<iic.h>
#include<PCF8563.h>
receiveBuf 	receiveStr;

void initMCU()
{	
	receiveStr.size = 0;
	setUART();
	//time_init(); //时钟芯片初始时间设置
    pcf_init();
	enableUartPort();

	P1M0 = 0x00; //P1推挽输出
	P1M1 = 0xff;
}

// 波特率600  自动获取mcu内部时钟   FSOC约为5447000
void setUART()
{
	int BAUD = 600;
	BYTE *p = 0xF9;
	long FSOC = 0;
	long FSOCb =  *p;
	long FSOCc =  *(++p);
	long FSOCd =  *(++p);
	FSOC = (FSOCb<<16)+ (FSOCc<<8) +FSOCd;

	SCON=0x50;
	TMOD = 0x20;  //八位自动重装
	
	TH1 = (int)(256-(FSOC/12.0/32/BAUD));
	TL1 = TH1;
	TR1=1;
	ES=1;
	EA=1;
}
//使能串口
void enableUartPort()
{
	P3=0x03;//使能串口
}
//撤销串口
void disableUartPort()
{
	P3=0x00;//撤销
}