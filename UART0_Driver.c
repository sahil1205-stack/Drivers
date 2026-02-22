//#include<lpc213x.h>
#include"header.h"

#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR & 1)

void uart0_init(ui baud){
	int PCLK, result;
	
	int a[] = {15, 60, 30, 0, 1};
	PCLK = a[VPBDIV] * 1000000;
	result = PCLK / (16 * baud);
	
	PINSEL0 |= 0X05;
	
	U0LCR = 0X83;
	
	U0DLL = result & 0xFF;
	U0DLM = (result >> 8) & 0XFF;
	
	U0LCR = 0x03;;
}

void uart0_tx(uc data){
	U0THR = data;
	while(THRE == 0);
}

uc uart0_rx(void){
	while(RDR == 0);
	return U0RBR;
}

void uart0_tx_str(char *p){
	while(*p){
		uart0_tx(*p);
		p++;
	}
}

void uart0_int(int num){
	
	uc a[100];
	
	int i=0;
	for(; num; num /= 10){
		a[i] = num%10+48;
		i++;
	}
	
	for(int j=i-1; j>=0; j--){
		uart0_tx(a[j]);
	}
	
}
