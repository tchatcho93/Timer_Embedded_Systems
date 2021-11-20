#include <stdio.h>

#define CST(addr) *((volatile unsigned int *)(addr))


#define RCC_BASE				(0x40023800UL)
#define AHBEN_R_OFFSET			(0x1CUL)	
#define RCC_AHBEN_R				(*(volatile unsigned int *)(RCC_BASE + AHBEN_R_OFFSET))

#define GPIOAEN					(1U<<0)

#define GPIOA_BASE 				(0x40020000UL)

#define GPIO_MODE_OFFSET 		(0x00UL)
#define GPIO_OTYPE_OFFSET		(0x04UL)
#define GPIO_PUP_PDOWN_OFFSET 	(0x0CUL)
#define GPIO_ODR_OFSSET			(0x14UL)
#define GPIO_BSRROFFSET 		(0x18UL)


#define GPIOA_MODER				(*(volatile unsigned int *)(GPIOA_BASE + GPIO_MODE_OFFSET))
#define GPIOA_PU_PBR			(*(volatile unsigned int *)(GPIOA_BASE + GPIO_PUP_PDOWN_OFFSET))
#define GPIOA_ODR				(*(volatile unsigned int *)(GPIOA_BASE + GPIO_ODR_OFSSET))
#define GPIOA_BSRR				(*(volatile unsigned int *)(GPIOA_BASE + GPIO_BSRROFFSET))

#define PIN5 					(1U<<5)
#define LED 					PIN5


int main(void)
{

	RCC_AHBEN_R |= GPIOAEN;

 	/* Configure Pin 5 as output */	
	GPIOA_MODER |= (1<<10);
	GPIOA_MODER &= ~(1<<11);
	
	/* No pull-up, pull-down resistor on pin 5*/
	//GPIOA_PU_PBR &= ~(1 << 10 | 1 << 11);

	
	int i;
	while(1){

		//GPIOA_ODR |= LED;
		
		GPIOA_ODR ^= LED;
		for (i = 0; i < 1000000; i++) {}
	}
	
	return 0;
}
