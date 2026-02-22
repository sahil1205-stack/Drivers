#include"header.h"

#define CS0 (1<<7)

void spi0_init(void){
	IODIR0 |= CS0;      // select chip select pin.
	IOSET0 |= CS0;      // Diselect slave.
	PINSEL0 |= 0X1500;  // P0.6->MOSI, P0.5->MISO, P0.4->CLK
	S0SPCCR = 150;      // 100 KBPS
	S0SPCR = 0X20;      // CPOL = CPHA = 0; (MODE-0)
}

#define SPIF ((S0SPSR>>7) & 1)

uc spi0(uc data){
	uc temp;
	S0SPDR = data;
	while(SPIF == 0);
	
	temp = S0SPDR;
	return temp;
}

usi mcp3204_read(uc ch){
	uc byteH, byteL, channel = 0;
	usi temp;
	
	channel = ch << 6;     // Set channel number (bit 6 & 7)
	
	IOCLR0 = CS0;          // select slave
	spi0(0x06);            // first transfer - start mode, SGL, D2 (Based on MCP3204)
	byteH = spi0(channel); // second transfer - ch0 selected
	byteL = spi0(0x00);    // third transfer - master(don't care) 
	IOSET0 = CS0;          // Diselect slave
	
	byteH &= 0x0f;         // Masking lower four bits;
	temp = (byteH << 8) | byteL;  // Combined them both (12 bits)
	return temp;
}


