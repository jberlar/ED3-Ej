#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


#define LED (1<<22)

void configGPIO(void);
void delay(uint32_t tiempo);

int main(void) {

		uint32_t relojCpu = SystemCoreClock;

		configGPIO();

		while(1){
			if((LPC_GPIO2->FIOPIN)&(1<<10)){
				tiempo = 1000000;
			}
			else{
				tiempo= 100000;
			}

			LPC_GPIO0->FIOCLR |= (LED);
			delay(tiempo);
			LPC_GPIO0->FIOSET |= (LED);
			delay(tiempo);
		}


    return 0 ;
}

void configGPIO(void){
	LPC_PINCON->PINSEL1 &= ~(0b11<<12);
	LPC_GPIO0->FIODIR |= (LED);
	LPC_GPIO2->FIODIR &= ~(1<<10);
	LPC_PINCON->PINMODE0 |= (3<<20);
}

void delay(uint32_t tiempo){
	uint32_t counter;
	for(counter = 0; counter < tiempo; counter++){};
}

