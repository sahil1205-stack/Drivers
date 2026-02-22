#include"header.h"

#define DONE ((ADDR>>31)&1)

void adc_init(void){
		PINSEL1 |= 0X15400000;  // All channels are selected
		ADDR |= 0X200400;       // 
}

uc adc_read(uc ch){	
	uc result;
	
	ADCR |= (1<<ch);    // channel select
	ADCR |= (1<<24);    // Start conversion
	
	while(DONE == 0);
	
	ADCR ^= (1<<24);    // Stope conversion
	ADCR ^= (1<<ch);    // Diselect channel
	
	result = (ADDR >> 6 & 0x3FF);  // 10-bit result extraction
	return result;
}


uc temp_data(void){
	ui adc_val;
	float vout;
	float temperature = 0 ;
	
	adc_val = adc_read(1);
	vout = (adc_val * 3.3) / 1024;
	temperature = (vout - 0.5) / 0.01;
	
	return temperature;
}

uc pot_data(void){
	ui adc_val;
	float vout = 0;
	
	adc_val = adc_read(2);
	vout = (adc_val * 3.3) / 1024;
	
	return vout;
}

