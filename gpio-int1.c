#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#define LED (1<<22)

void configGPIO(void);
void delay(uint32_t tiempo);
void confIntGPIO(void);
void EINT3_IRQHandler(void);
uint8_t inte;

int main(void) {

		uint32_t relojCpu = SystemCoreClock;

		configGPIO();
		confIntGPIO();

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
	LPC_GPIO2->FIODIR &= ~(1<<10);
	LPC_PINCON->PINMODE0 |= (3<<20);
	return;
}

void delay(uint32_t tiempo){
	uint32_t counter;
	for(counter = 0; counter < tiempo; counter++){};
	return;
}

//RE Int @ P0.15
void confIntGPIO(void){
	LPC_GPIOINT->IO0IntEnR |= (1<<15);
	LPC_GPIOINT->IO0IntClr |= (1<<15);
	NVIC_Enable(EINT3_IRQn);
	return;
}

void EINT3_IRQHandler(void){
	if(LPC_GPIOINT->IO0IntStatR & (1<<15)){
		inte++;
	}
	LPC_GPIOINT->IO0IntClr |= (1<<15);
}