/*can1_driver.c*/
#include <LPC21xx.H>
#include "header.h"

extern u8 flag;
extern CAN1 r1;
extern int op;

void CAN1_Rx_Handler(void) __irq{
        r1.id=C1RID;
        r1.dlc=(C1RFS>>16)&0xF;
        r1.rtr=(C1RFS>>30)&1;

        if(r1.rtr==0){
                r1.byteA=C1RDA;
                op=(r1.byteA&0xff);
                r1.byteB=C1RDB;
        }
        C1CMR=(1<<2);//*release/free receiver buffer
        flag=1;//further used in main func
        VICVectAddr=0;

}


void config_vic_for_can1(void){

        VICVectCntl5=26|(1<<5);//assign can1 rx intr to slot5
        VICVectAddr5=(u32)CAN1_Rx_Handler;//assign can1 isr addr to slot5
        VICIntEnable=(1<<26);//En CAN1 rx intr in VIC
        C1IER=1;//En CAN1 Rx Intr

}




void can1_init(void){

        VPBDIV=1;
        PINSEL1|=0x40000;
        C1MOD=1;
        AFMR=2;
        C1BTR=0x001C001D;//baudrate 125Kbps
        C1MOD=0;

}


#define RBS (C1GSR&1)

void can1_rx(CAN1 *ptr){
        while(RBS==0);//waiting for frame to receive
        ptr->id=C1RID;
        ptr->dlc=(C1RFS>>16)&0xF;//extract dlc
        ptr->rtr=(C1RFS>>30)&1;//extract rtr
        if(ptr->rtr==0){//if data-frame
                ptr->byteA=C1RDA;
                ptr->byteB=C1RDB;
        }
        C1CMR=(1<<2);//*release/free receiver buffer
}







#define TCS ((C1GSR>>3)&1)

void can1_tx(CAN1 v){

        C1TID1=v.id;
        C1TFI1=v.dlc<<16;//set dlc, rtr=0, ff=0
        if(v.rtr==0){//if data-frame
                C1TDA1=v.byteA;
                C1TDB1=v.byteB;
        }
        else
                C1TFI1|=(1<<30);//rtr=1

        C1CMR=0x21;//select txbuf1 & start xmission
        while(TCS==0);
}
