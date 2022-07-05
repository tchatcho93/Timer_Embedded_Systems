#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <stdio.h>

#define PORT_LED_VERTE GPIOA
#define LED_VERTE GPIO5


static void gpio_setup(void)
{
	/* Enable GPIOA clock. */
    rcc_periph_clock_enable(RCC_GPIOA);

	/* Set GPIO6 (in GPIO port B) to 'output push-pull'. */
	gpio_mode_setup(PORT_LED_VERTE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_VERTE);
}


static void timer_setup(void)
{

	rcc_clock_setup_pll(&rcc_clock_config[RCC_CLOCK_VRANGE1_HSI_PLL_24MHZ]);

	/* enable TIMER2 Clock*/
    rcc_periph_clock_enable(RCC_TIM2);

	/* Enable TIM2 interrupt. */
	nvic_enable_irq(NVIC_TIM2_IRQ);

	/* Reset TIM2 peripheral to defaults. */
	rcc_periph_reset_pulse(RST_TIM2);

	timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT,
		TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

	timer_set_prescaler(TIM2, 1000);

	/* Disable preload. */
	timer_disable_preload(TIM2);
	timer_continuous_mode(TIM2);

	/* count full range, as we'll updGPIOA ate compare valu
	 *
	 */
	timer_set_period(TIM2, 12000);

		/* Counter enable. */
		timer_enable_counter(TIM2);

		/* Enable Channel 1 compare interrupt to recalculate compare values */
		timer_enable_irq(TIM2, TIM_DIER_UIE);
	}

	void tim2_isr(void)
	{
		if (timer_get_flag(TIM2, TIM_SR_UIF)) {

			/* Clear compare interrupt flag. */
			timer_clear_flag(TIM2, TIM_SR_UIF);

			/* Toggle LED to indicate timer overflow. */
			gpio_toggle(PORT_LED_VERTE, LED_VERTE);
		}
	}

	int main(void)
	{
		gpio_setup();
		timer_setup();

		while (1) {


		}


		return 0;
	}
