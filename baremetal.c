#include <stdio.h>

#define CST(addr) *((volatile unsigned int *)(addr))


#define RCC_BASE				(0x40023800UL)
#define AHBEN_R_OFFSET			(0x0UL)	
#define RCC_AHBEN_R				CST(RCC_BASE + AHBEN_R_OFFSET)

#define GPIOAEN					(1U<<0)

#define GPIOA_BASE 				(0x40020000UL)

#define GPIO_MODE_OFFSET 		(0x00UL)
#define GPIO_OTYPE_OFFSET		(0x04UL)
#define GPIO_PUP_PDOWN_OFFSET 	(0x0CUL)
#define GPIO_ODR_OFSSET			(0x14UL)
#define GPIO_BSRROFFSET 			(0x18UL)


#define GPIOA_MODER				CST(GPIOA_BASE + GPIO_MODE_OFFSET)
#define GPIOA_PU_PBR			CST(GPIOA_BASE + GPIO_PUP_PDOWN_OFFSET)
#define GPIOA_ODR				CST(GPIOA_BASE + GPIO_ODR_OFSSET)
#define GPIOA_BSRR				CST(GPIOA_BASE + GPIO_BSRROFFSET)

#define PIN5 					(1U<<5)
#define LED 					PIN5




static void clock_setup(void)
{
	RCC_AHBEN_R |= GPIOAEN;
}

static void gpio_setup(void)
{
	/* Configure Pin 5 as output */	
	GPIOA_MODER |= (1<<10);
	GPIOA_MODER &= ~(1<<11);
	
	/* No pull-up, pull-down resistor on pin 5*/
	GPIOA_PU_PBR &= ~(1 << 10 | 1 << 11);
}

int main()
{
	clock_setup();
	gpio_setup();
	
	while(1){

		GPIOA_ODR |= LED;
		
		for (i = 0; i < 1000000; i++) {	/* Wait a bit. */
			__asm__("nop");
		}

		GPIOA_ODR &= ~LED;
	
		for (i = 0; i < 1000000; i++) {	/* Wait a bit. */
			__asm__("nop");
		}
	}
	
	return 0;
}
