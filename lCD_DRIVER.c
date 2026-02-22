#include<lpc21xx.h>
#include"header.h"

#define RS 1<<17
#define RW 1<<18
#define EN 1<<19

void lcd_data(ui data){
	IOCLR1 = 0XFE<<16;
	IOSET1 = (data & 0XF0) << 16;
	
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	
	delay(2);
	IOCLR1 = EN;
	
	IOCLR1 = 0XFE<<16;
	IOSET1 = (data & 0X0F) << 20;
	
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	
	delay(2);
	IOCLR1 = EN;
}

void lcd_cmd(ui cmd){
	
	IOCLR1 = 0XFE<<16;
	IOSET1 = (cmd & 0XF0) <<16;
	
	IOCLR1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	
	delay(2);
	IOCLR1 = EN;
	
	IOCLR1 = 0XFE<<16;
	IOSET1 = (cmd & 0X0F) << 20;
	
	IOCLR1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	
	delay(2);
	IOCLR1 = EN;
}

void lcd_string(char *p){
	while(*p){
		lcd_data(*p);
		p++;
	}
}
void lcd_cgram(void){
	
	ui a[8] = {0x0, 0xa, 0xa, 0x0, 0x11, 0xe, 0x0, 0x0};
	
	lcd_cmd(0x40);
	
	for(int i=0; i<8; i++)
		lcd_data(a[i]);
}

void lcd_integer(int num){
	
	int a[10], i=0;
	
	if(num == 0)
		lcd_data('0');
	
	if(num<0){
		lcd_data('-');
		num = -num;
	}
	
	while(num>0){
		a[i] = num%10 + 48;
		num = num/10;
		i++;
	}
	
	for(i=i-1; i>=0; i--)
		lcd_data(a[i]);
}

		

void lcd_init(void){
	
	IODIR1 = 0XFE<<16;
	
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0c);
	lcd_cmd(0x01);
}
