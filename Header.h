#include<lpc21xx.h>

typedef struct my_time{
	int hour;
	int minute;
	int second;
}TIME;

typedef unsigned int ui;
typedef unsigned char uc;
typedef unsigned short usi;

void delay(ui ms);
void uart0_init(ui baud);
void uart0_binary(uc num);
void uart0_tx(uc num);
int uart0_atoi(char *p);
void uart0_string(char *p);
void uart0_int(int num);

void CONFIG_INTR(void);
void UART0_EN(void);

void lcd_init(void);
void lcd_cmd(ui cmd);
void lcd_data(ui data);
void lcd_string(char *p);
void lcd_integer(int num);

void i2c_init(void);
void i2c_send(uc sa, uc mem, uc data);
uc i2c_read(uc sa, uc mem);

void spi0_init(void);
uc spi0(uc data);
usi mcp3204_read(uc ch);

void adc_init(void);
uc adc_read(uc ch);
uc temp_data(void);
uc pot_data(void);
