#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


int main(void) {

    LPC_PINCON->PINSEL1 &= ~(0x03<<12);
	LPC_PINCON->PINSEL7 &= ~(0x15<<18);

	LPC_PINCON->PINMODE1 &= ~(0x03<<12);
	LPC_PINCON->PINMODE1 |= 0x01<<13;
	LPC_PINCON->PINMODE7 &= ~(0x15<<18);
	LPC_PINCON->PINMODE7 |= 0x01<<19;
	LPC_PINCON->PINMODE7 |= 0x01<<21;

	LPC_GPIO0->FIODIR = 0XFFFFFFFF;
	LPC_GPIO3->FIODIR = 0XFFFFFFFF;


    while(1) {
        LPC_GPIO0->FIOSET |= 1<<22;
        LPC_GPIO3->FIOSET |= 0b11<<25;
        for (int i=0; i<10000000; i++);
        LPC_GPIO0->FIOCLR |= 1<<22;
        for (int i=0; i<10000000; i++);
        LPC_GPIO3->FIOCLR |= 0b1<<25;
        for (int i=0; i<10000000; i++);
        LPC_GPIO3->FIOCLR |= 0b1<<26;
        for (int i=0; i<10000000; i++);
    }

    return 0 ;
}
