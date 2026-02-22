/* Interrupt nodeA */

#include"header.h"

extern CAN1 v1;

void HEADLIGHT_ISR(void) __irq{
	
	static int hl = 0;
	
	hl = !hl;
	
	if(hl){
		v1.byteA = 0x10;
		can1_tx(v1);
		uart0_string("headlight on\r\n");
	}
	else{
		v1.byteA = 0x11;
		can1_tx(v1);
		uart0_string("headlight off\r\n");

	}
	
	EXTINT |= 1;
	VICVectAddr = 0;

}

void RIGHT_IN_ISR(void) __irq{
	
	static int RI = 0;
	
	RI = !RI;
	
	if(RI){
		v1.byteA = 0x20;
		can1_tx(v1);
		uart0_string("Right indicator on\r\n");
	}
	else{
		v1.byteA = 0x21;
		can1_tx(v1);
		uart0_string("Right indicator off\r\n");

	}
	
	EXTINT |= (1<<1);
	VICVectAddr = 0;
	
}

void LEFT_IN_ISR(void) __irq{
	
	static int LI = 0;
	
	LI = !LI;
	
	if(LI){
		v1.byteA = 0x30;
		can1_tx(v1);
		uart0_string("Left indicator on\r\n");

	}
	else{
		v1.byteA = 0x31;
		can1_tx(v1);
		uart0_string("Left indicator off\r\n");
	}
	
	EXTINT |= (1<<2);
	VICVectAddr = 0;
}

void EINT_INIT(void){
	
	PINSEL1 |= 0X1;                  // P0.16 EINT0
	PINSEL0 |= 0XC0C0;               // P0.3(EINT2) & P0.7(EINT1)
	
	EXTMODE = 7;                     // All EINT = EDGE Triggered.
	EXTPOLAR = 0;                    // ALL EINT = Active Low.
	
	VICIntSelect = 0;                // All IRQ
	
	VICVectCntl0 = 14 | (1<<5);      // EINT0 = Headlight.
	VICVectAddr0 = (ui)HEADLIGHT_ISR;
	VICVectCntl1 = 15 | (1<<5);      // EINT1 = Right Indicator.
	VICVectAddr1 = (ui)RIGHT_IN_ISR;
	VICVectCntl2 = 16 | (1<<5);      // EINT2 = Left Indicator.
	VICVectAddr2 = (ui)LEFT_IN_ISR;
	
	VICIntEnable = (7<<14);
}
