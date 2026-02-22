#include<lpc21xx.h>
#include"header.h"

#define LED2 (1<<18)
ui monitor_flag;

void EINT0_ISR(void) __irq{
	
	static uc flag=0;
	
	flag = !flag;
	
	if(flag)
		IOCLR0 = LED2;
	else
		IOSET0 = LED2;
	
	monitor_flag = !monitor_flag;
	EXTINT = (1<<0);
	VICVectAddr = 0;
}

void CONFIG_VIC(void){
	
	VICIntSelect = 0;
	VICVectCntl0 = 14 | (1<<5);
	VICVectAddr0 = (ui)EINT0_ISR;
	VICIntEnable = (1<<14);

}

void EN_EINT0(void){
	PINSEL1 |= 1;       //PIN P0.16
	IODIR0 |= LED2;
	EXTMODE = (1<<0); // EDGE TRIGGERD
	EXTPOLAR = 0;     // ACTIVE LOW
}