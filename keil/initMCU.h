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

// ������600  �Զ���ȡmcu�ڲ�ʱ��   FSOCԼΪ5447000
void setUART();

//ʹ�ܴ���
void enableUartPort();
void disableUartPort();
		
#endif