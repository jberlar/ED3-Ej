#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#define LED (1<<22)

void configGPIO(void);
void delay(uint32_t tiempo);
void confIntExt(void);
void EINT0_IRQHandler(void);
uint8_t inte = 0;

int main(void) {

		uint32_t tiempo;

		configGPIO();
		confIntExt();

		while(1){
			if(inte%2){
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
	LPC_GPIO0->FIODIR |= (LED);
	return;
}

void delay(uint32_t tiempo){
	uint32_t counter;
	for(counter = 0; counter < tiempo; counter++){};
	return;
}

//RE Int @ P2.10
void confIntExt(void){
	LPC_PINCON->PINSEL4 |= (1<<20);
	LPC_SC->EXTMODE |= 1;
	LPC_SC->EXTPOLAR |= 1; 
	LPC_SC->EXTINT |= 1; //clear flag
	NVIC_Enable(EINT0_IRQn);
	return;
}

void EINT0_IRQHandler(void){
	inte++;
	LPC_SC->EXTINT |= 1;
	return;
}
