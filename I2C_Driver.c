#include"header.h"

#define SI ((I2CONSET >> 3) & 1)

void i2c_init(void){
	
	//PINSEL0 |= 0X50;   // p0.2 -> SCL p0.3 -> SDA 
	PINSEL0 |=  (3 << 4) | (3 << 6);

	I2CONSET = (1<<6); // Enable I2C interface
	I2SCLH=I2SCLL=75;  // 100Kbps speed

}

void i2c_send(uc sa, uc mem, uc data){
	
	I2CONSET = (1<<5); // Generate start condition;
	I2CONCLR = (1<<3); // SI = 0;
	while(SI == 0);
	I2CONCLR = (1<<5); // STA = 0;
	
	if(I2STAT != 0X08){
		uart0_string("ERROR: start condition\r\n ");
		goto exit;
	}
	
	I2DAT = sa;
	I2CONCLR = (1<<3); // SI = 0;
	while(SI == 0);
	if(I2STAT == 0X20){
		uart0_string("ERROR: SA + W \r\n");
		goto exit;
	}
	
	I2DAT = mem;
	I2CONCLR = (1<<3); 
	while(SI == 0);
	if(I2STAT == 0X30){
		uart0_string("ERROR: Memory address\r\n");
		goto exit;
	}
	
	I2DAT = data;
	I2CONCLR = (1<<3);
	while(SI == 0);
	if(I2STAT == 0x30){
		uart0_string("ERROR: data\r\n");
		goto exit;
	}
	
exit:
	I2CONSET = (1<<4);
	I2CONCLR = (1<<3);
	
}

uc i2c_read(uc sa, uc mem){
	
	uc temp = 0;
	
	I2CONSET = (1<<5);
	I2CONCLR = (1<<3);
	while(SI == 0);
	I2CONCLR = (1<<5);
	if(I2STAT != 0X08){
		uart0_string("Start condition\r\n");
		goto exit;
	}
	
	I2DAT = sa;
	I2CONCLR = (1<<3);
	while(SI == 0);
	if(I2STAT == 0x20){
		uart0_string("sa+w\r\n");
		goto exit;
	}
	
	I2DAT = mem;
	I2CONCLR = (1<<3);
	while(SI == 0);
	if(I2STAT == 0x30){
		uart0_string("memory address \r\n");
		goto exit;
	}
	
	I2CONSET = (1<<5);
	I2CONCLR = (1<<3);
	while(SI == 0);
	I2CONCLR = (1<<5);
	
	I2DAT = sa|1;
	I2CONCLR = (1<<3);
	while(SI == 0);
	if(I2STAT == 0x48){
		uart0_string("SA+R\r\n");
		goto exit;
	}
	
	I2CONCLR = (1<<3);
	while(SI == 0);
	temp = I2DAT;
	
exit:
	I2CONSET = (1<<4);
	I2CONCLR = (1<<3);
	
	return temp;
}



