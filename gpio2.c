#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#define LED (1<<22)

void configGPIO(void);
void delay(void);

int main(void) {

		configGPIO();

		while(1){
			LPC_GPIO0->FIOCLR |= (LED);
			delay();
			LPC_GPIO0->FIOSET |= (LED);
			delay();
		}


    return 0 ;
}

void configGPIO(void){
	LPC_PINCON->PINSEL1 &= ~(0b11<<12);
	LPC_GPIO0->FIODIR |= (LED);
}

void delay(void){
	uint32_t counter;
	for(counter = 0; counter < 600000; counter++){};
}
