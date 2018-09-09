#ifndef INITMCU_H
#define INITMCU_H

typedef struct 
{
	char buf[50];
	char size;	
} receiveBuf ; 


typedef unsigned char BYTE;

typedef struct
{
	BYTE hour;
	BYTE min;
	BYTE sec;
	BYTE week;
}Time;

	 
void initMCU();

// 波特率600  自动获取mcu内部时钟   FSOC约为5447000
void setUART();

//使能串口
void enableUartPort();
void disableUartPort();
		
#endif