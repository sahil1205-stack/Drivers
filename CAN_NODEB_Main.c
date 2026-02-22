/*main_nodeB_interrupt.c*/

#include <LPC21xx.H>

#include "header.h"

#define LED1 (1<<17) //L HL
#define LED2 (1<<18) //R HL
#define LED3 (1<<19) // head light

CAN1 r1;

u8 flag;
int op;

main(){

        can1_init();
				config_vic_for_can1();
				lcd_init_8();
				
        IODIR0|=LED1|LED2|LED3;
        IOSET0|=LED1|LED2|LED3;
	
        while(1){

                //can1_rx(&r1);
                if(flag==1){
                        flag=0;//for next frame

									switch(op){
                        case 0x10: IOCLR0=LED1;
												lcd_tx_string("Head_Light On");
                        delay_ms(50);
                        //flag=1;
                         break;


                        case 0x11: IOSET0=LED1;
                       lcd_tx_string("Head_Light Off");
                        delay_ms(50);
                        //flag=1;
                         break;
										
                        case 0x12:lcd_tx_string("right Indicator on");
																	delay_ms(50);
												while(op==0x12)
                        {
                          IOCLR0=LED2;
                          delay_ms(50);
                          IOSET0=LED2;
                          delay_ms(50);

                        }
                        break;
												
                        case 0x13:
                        IOSET0=LED2;
                        lcd_tx_string("right indicator off");
                        //flag=1;
                        break;

                        case 0x14:lcd_tx_string("left Indicator on");
                        delay_ms(50);
                        while(op==0x14)
                        {
                          IOCLR0=LED3;
                          delay_ms(50);
                          IOSET0=LED3;
                          delay_ms(50);

                        }
                        break;
                        case 0x15:
                        IOSET0=LED3;
                        lcd_tx_string("left Indicator off");
                        //flag=1;
                        break;
                }

        }

        }

}
