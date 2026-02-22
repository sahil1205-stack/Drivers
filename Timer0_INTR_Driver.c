#include"header.h"

int flag=0, flag2 = 0;
char a[300];

void TIMER0_ISR(void) __irq
{
	if(T0IR & 1){
		T0IR = 1;
		flag = !flag;
	}
	if((T0IR >> 1)&1){
		T0IR = 1<<1;
		flag2 = !flag2;
	}
	
	VICVectAddr = 0;
}



void CONFIG_VIC(void){
	
	VICIntSelect = 0;
	VICVectCntl0 = 4 | (1<<5);
	VICVectAddr0 = (ui)TIMER0_ISR;	
	
	VICIntEnable = (1<<4);

}

void TIMER0_INIT(int sec){
	
	

	T0TC = 0;
	T0PR = 15000;
	
	T0MR0 = sec*10-1;
	T0MCR |= 0X03;
	
	T0MR1 = sec;
	T0MCR |= (0X01)<<3;

	T0TCR = 1;
}



void UART0_INIT(void){
	U0IER = 3;
}
