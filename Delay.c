#include<lpc21xx.h>

typedef unsigned int u64;

void delay_ms(u64 ms){
	T0PC = 0;
	T0PR = 15000-1;
	T0TC = 0;
	T0TCR = 1;
	
	while(T0TC < ms);
	
	T0TCR = 0;
}
