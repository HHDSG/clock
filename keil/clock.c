#include<STC12C54.h>
#include<initMCU.h>
#include<iic.h>
#include<PCF8563.h>
#include<string.h>

//#define DEBUG 
#define CMD_SET_TIME 1
#define SET_MODE 1
#define RUN_MODE 0
#define setKey P37
//0~F 点 共阴
BYTE disPlayCode[]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x80};

volatile bit busy;	//串口发送忙
extern receiveBuf receiveStr;  //串口接收数据buffer


void sendData(BYTE dat);
void sendString(char *s);
int phaseCMD(char *cmd);
bit switchRunMode(bit runMode);
void getTime(Time *curTime);
void setTime(Time *setTime);
void disPlayTime(Time *curTime);

int main()
{
	int i=0;
	Time curTime;
	bit runMode = RUN_MODE;

	Time temp;
	temp.hour=0x20;
	temp.min=0x29;
	temp.week=0x3;//减一

	setKey =1;
	delayNus(10000);
	initMCU();
	disableUartPort();

	//setTime(&temp);	
	
	
	while(1)																					 
	{		
		if(setKey==0)
		{
			//runMode = switchRunMode(runMode);
		}
		if(runMode == SET_MODE )
		{
			P1 = disPlayCode[5];
		}
		if(runMode == RUN_MODE )
		{
			getTime(&curTime);
			disPlayTime(&curTime);
		}
		
	}
	return 0;
}

void disPlayTime(Time *curTime)
{
	int delayNum =10;
	static BYTE preSec = 0;
	static bit dotLight = 0;

	P1= disPlayCode[curTime->hour/10];
	P17=dotLight;
	if(curTime->sec!=preSec)
	{
		dotLight = ~dotLight;
		preSec = curTime->sec;
	}
	P32=0;
	delayNus(delayNum);
	P32=1;

	P1 = disPlayCode[curTime->hour%10];
	P17 = (curTime->week & 0x04) >>2; 
	P33=0;
	delayNus(delayNum);
	P33=1;

	P1 = disPlayCode[curTime->min/10];
	P17 = (curTime->week & 0x02) >>1;
	P34=0;
	delayNus(delayNum);
	P34=1;

	P1 = disPlayCode[curTime->min%10];
	P17 = curTime->week & 0x01;
	P35=0;
	delayNus(delayNum);
	P35=1; 
	
}

void getTime(Time *curTime)
{
	curTime->sec=0x7f&iic_rec_add_byte(0x02);    //读取秒
	curTime->sec = bcd_dec(curTime->sec);

	curTime->min=0x7f&iic_rec_add_byte(0x03);   //读取分钟
	curTime->min = bcd_dec(curTime->min);

	curTime->hour=0x3f&iic_rec_add_byte(0x04);  //读取小时
	curTime->hour = bcd_dec(curTime->hour);

	curTime->week=0x07&iic_rec_add_byte(0x06);  //读取星期
	curTime->week = curTime->week + 1;//1~7
}

void setTime(Time *setTime) //设置PCF8563时间
{
	iic_send_add_byte(0x02,setTime->sec);         //0秒  BCD编码
	iic_send_add_byte(0x03,setTime->min);         //0分钟    
	iic_send_add_byte(0x04,setTime->hour);          //0小时  
	iic_send_add_byte(0x06,setTime->week);	//星期
}


bit switchRunMode(bit runMode)
{
	delayNus(10000);//大约20ms
	
	if(setKey == 0)//按键按下
	{
		return runMode;
	}
	delayNus(50000);
	if(setKey != 0)//按键抬起
	{
		return runMode;
	}

	return runMode==RUN_MODE? SET_MODE:RUN_MODE;
}	 

 
int phaseCMD(char *cmd)
{
	char const *cmdSetTime = "setTime";
	char temp[20]={'\n'};
	if(receiveStr.size ==0)
	{
		return 0;
	}
	strncpy(temp,cmd,7);
	if(strcmp(temp,cmdSetTime)==0)
	{
		return  CMD_SET_TIME;
	}
	return 0;
}
 


void Uart_Isr() interrupt 4 using 1
{
	char temp;
	if(RI)
	{
		RI=0;
		temp = SBUF;
	    receiveStr.buf[receiveStr.size++] = temp;
		if(receiveStr.size==50)
			receiveStr.size = 0;
		if(temp=='\n')
		{ 	
			receiveStr.size = 0;	
		}
	}
	if(TI)
	{
		TI=0;
		busy = 0;
	}
}

void sendString(char *s)
{
	while(*s != '\n' && *s!= 0)
	{
		sendData(*s++);
	}
	sendData('\n');
}

void sendData(BYTE dat)
{
	while(busy);
	busy=1;
	SBUF=dat;
}
