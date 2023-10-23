/* example program: external interrupt on PB0
 * enables builtin led of stm32f103 "bluepill" board
 * on rising and disables it on falling
 */
#include "include/hal/gpio_stm32f1.h"
#include "include/hal/rcc_stm32f1.h"
#include "include/hal/exti_stm32f1.h"
#include "include/hal/reg.h"

#define NVIC_ISER0 REG(0xE000E100)
#define NVIC_IPR1 REG(0xE000E400 + 1 * 4)
#define NVIC_ISPR0 REG(0xE000E200)
#define NVIC_ICPR0 REG(0xE000E280)
#define AFIO_EXTICR1 REG(0x40010008)

volatile char interrupted = 0;

int
main(void)
{
	/* enable clock on the desired pin bank */
	rcc_periph_enable(RCC_AFIOEN);
	rcc_periph_enable(RCC_IOPBEN);
	rcc_periph_enable(RCC_IOPCEN);

	/* enable the led output */
	gpio_set_mode(GPIOC, 13, GPIO_MODE_OUTPUT_10_MHZ);
	gpio_set_cnf(GPIOC, 13, GPIO_CNF_OUTPUT_PUSH_PULL);
	/* PC13 is active low */
	gpio_set_pin(GPIOC, 13);

	/* configure pb 0 pin as input floating */
	gpio_set_mode(GPIOB, 0, GPIO_MODE_INPUT);
	gpio_set_cnf(GPIOB, 0, GPIO_CNF_INPUT_FLOATING);

	/* configure afio so pb0 as external interrupt
	 * TODO: AFIO peripheral
	 */
	AFIO_EXTICR1 = 1UL;

	/* enable exti0 on both falling and rising */
	enable_rising_exti(EXTI0);
	enable_falling_exti(EXTI0);

	/* enable exti0 */
	enable_exti(EXTI0);

	/* enable interrupt line in nvic */
	NVIC_ISER0 = 1UL << 6;

	/* enable general interrupts */
	asm("CPSIE i");

	while (1) {
		if (interrupted) {
			gpio_toggle_pin(GPIOC, 13);
			interrupted = 0;
		}
	}

	return 0;
}

extern void _estack(void);

/* firmware */
__attribute__((naked, noreturn)) void
_reset(void)
{
	extern long int _sbss, _ebss, _sdata, _edata, _sidata;
	long *dst, *src;

	/* zero out bss */
	for (dst = &_sbss; dst < &_ebss; dst++)
		*dst = 0;

	/* copy global variable values from rom to ram */
	dst = &_sdata;
	src = &_sidata;
	while (dst < &_edata) {
		*dst = *src;
		dst++;
		src++;
	}

	main();

	while (1);
}

void
exti0_isr(void)
{
	interrupted = 1;
	if (is_pending_exti(EXTI0))
		clear_pending_exti(EXTI0);
}

__attribute__((section(".vectors"))) void (*const vectors[84])(void) = {
	_estack,
	_reset,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	[22] = exti0_isr
};
