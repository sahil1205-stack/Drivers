/* CAN1 Driver */

#include"header.h"
#define TCS ((C1GSR>>3)&1)

void can1_init(void){
	
	VPBDIV |= 1;
	PINSEL1 |= 0x40000;
	
	C1MOD = 1;        // Reset Mode On
	AFMR = 2;         // Accept All
	C1BTR = 0x1C001D; // 125KBPS BaudRate
	C1MOD = 0;        // Reset Mode Off

}

void can1_tx(CAN1 V){
	
	C1TID1 = V.id;        
	C1TFI1 = (V.dlc<<16); // Set DLC, rtr = 0, ff=0
	
	if(V.rtr == 0){     // Data Frame
		C1TDA1 = V.byteA;
		C1TDB1 = V.byteB;
	}
	else{
		C1TFI1 |= (1<<30);
	}
	
	C1CMR = 0x21;  // TxBuff-1 & Start Tx.
	while(TCS == 0); //block till data gets transmitted.
	
}
