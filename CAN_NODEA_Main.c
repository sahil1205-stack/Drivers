/* Node A main */

#include"header.h"

CAN1 v1;

int main(){
	can1_init();
	uart0_init(9600);
	
	EINT_INIT();
	
	// Default values :- 
	v1.id = 0x501;   // Only one ID because only one node is present.
	v1.dlc = 1;
	v1.rtr = 0;
	v1.byteA = 0x00;
	v1.byteB = 0x00;
	
	uart0_string("Start\r\n");
	while(1);
}
