#ifndef GPIO_STM32F1_C
#define GPIO_STM32F1_C

#include "gpio_stm32f1.h"

/* TODO:
 * gpio_pin functions
 */
/* algorithm:
 * checking for valid input data
 * 	-> non-null gpiox, mode between 0b00 and 0b11, pin number below 15
 * 	-> gpiox within valid range
 * clear current setting
 * put in new setting
 */
static void
gpio_set_mode(struct gpio *gpiox, unsigned char pin_number, char mode)
{
	if (!GPIOX_IN_RANGE(gpiox) || mode > 0b11 || pin_number > 15)
		return;
	
	if (pin_number < 8) {
		gpiox->CRL &= ~((unsigned int)0b11 << pin_number * 4);
		gpiox->CRL |= (unsigned int)mode << pin_number * 4;
	} else {
		gpiox->CRH &= ~((unsigned int)0b11 << (pin_number - 8) * 4);
		gpiox->CRH |= (unsigned int)mode << (pin_number - 8) * 4;
	}
}

/* algorithm:
 * checking for valid input data
 * 	-> non-null gpiox, cnf between 0b00 and 0b11, pin number below 15
 * 	-> gpiox within valid range
 * clear current setting
 * put in new setting
 */
static void
gpio_set_cnf(struct gpio *gpiox, unsigned char pin_number, char cnf)
{
	if (!GPIOX_IN_RANGE(gpiox) || cnf > 0b11 || pin_number > 15)
		return;
	
	if (pin_number < 8) {
		gpiox->CRL &= ~((unsigned int)0b11 << (pin_number * 4 + 2));
		gpiox->CRL |= (unsigned int)cnf << (pin_number * 4 + 2);
	} else {
		gpiox->CRH &= ~((unsigned int)0b11 << ((pin_number - 8) * 4 + 2));
		gpiox->CRH |= (unsigned int)cnf << ((pin_number - 8) * 4 + 2);
	}
}

/* algorith:
 * decode pin notationt o pin bank and pin number
 * call gpio_set_mode
 */
static void
gpio_pin_set_mode(unsigned short pin, char mode)
{
	unsigned char pin_bank, pin_number;

	pin_bank = PIN_BANK(pin);
	pin_number = PIN_NUMBER(pin);

	if (pin_bank < 'A' || pin_bank > 'G')
		return;
	
	/* other error checking is done by the function called */

	gpio_set_mode(GPIO_FROM_BANK(pin_bank), pin_number, mode);
}

/* algorith:
 * decode pin notationt o pin bank and pin number
 * call gpio_set_cnf
 */
static void
gpio_pin_set_cnf(unsigned short pin, char cnf)
{
	unsigned char pin_bank, pin_number;

	pin_bank = PIN_BANK(pin);
	pin_number = PIN_NUMBER(pin);

	if (pin_bank < 'A' || pin_bank > 'G')
		return;
	
	/* other error checking is done by the function called */

	gpio_set_cnf(GPIO_FROM_BANK(pin_bank), pin_number, cnf);
}

/* algorithm:
 * error checking
 * get data from register
 */
static char
gpio_get_mode(struct gpio *gpiox, unsigned char pin_number)
{
	if (!GPIOX_IN_RANGE(gpiox) || pin_number > 15)
		return 0xFF;
	
	if (pin_number < 8)
		return gpiox->CRL & ((unsigned int)0b11 << pin_number * 4);
	else
		return gpiox->CRH & ((unsigned int)0b11 << (pin_number - 8) * 4);
}

static char
gpio_get_cnf(struct gpio *gpiox, unsigned char pin_number)
{
	if (!GPIOX_IN_RANGE(gpiox) || pin_number > 15)
		return 0xFF;
	
	if (pin_number < 8)
		return gpiox->CRL & ((unsigned int)0b11 << (pin_number * 4 + 2));
	else
		return gpiox->CRH & ((unsigned int)0b11 << ((pin_number - 8) * 4 + 2));
}

/* TODO */
#if 0
static char gpio_pin_get_mode(unsigned short);
static char gpio_pin_get_cnf(unsigned short);
#endif

/* algorithm:
 * error checking/input data validation
 * this function uses the GPIO_BSRR register to set the coresponding bit
 * it does not check that the pin is in the output mode
 */
static void
gpio_set_pin(struct gpio *gpiox, unsigned char pin_number)
{
	if (!GPIOX_IN_RANGE(gpiox) || pin_number > 15)
		return;
	/*
	if (gpio_get_mode(gpiox, pin_number) == GPIO_MODE_INPUT)
		return;
	*/
	gpiox->BSRR |= (unsigned int)1 << pin_number;
}

/* algorithm:
 * error checking/input data validation
 * this function uses the GPIO_BSRR register to reset/clear the coresponding bit
 * it does not check that the pin is in the output mode
 */
static void
gpio_clear_pin(struct gpio *gpiox, unsigned char pin_number)
{
	if (!GPIOX_IN_RANGE(gpiox) || pin_number > 15)
		return;
	/*
	if (gpio_get_mode(gpiox, pin_number) == GPIO_MODE_INPUT)
		return;
	*/
	gpiox->BSRR |= (unsigned int)1 << (pin_number + 16);
}

/* algorithm:
 * error checking/input data validation
 * this function uses the GPIO_ODR register to toggle the coresponding bit
 * it does not check that the pin is in the output mode
 */
static void
gpio_toggle_pin(struct gpio *gpiox, unsigned char pin_number)
{
	if (!GPIOX_IN_RANGE(gpiox) || pin_number > 15)
		return;
	/*
	if (gpio_get_mode(gpiox, pin_number) == GPIO_MODE_INPUT)
		return;
	*/
	gpiox->ODR ^= (unsigned int)1 << pin_number;
}


#if 0
static void gpio_pin_set_pin(unsigned short);
static void gpio_pin_clear_pin(unsigned short);
static void gpio_pin_toggle_pin(unsigned short);
#endif

/* algorithm:
 * error checking/data validation
 * this function uses the GPIO_IDR register to get the state
 * it does not check the mode or cnf of the regiset TODO (should be different
 * depending on the pin mode and cnf
 */
static char
gpio_state(struct gpio *gpiox, unsigned char pin_number)
{
	if (!GPIOX_IN_RANGE(gpiox) || pin_number > 15)
		return 0xFF;
	return gpiox->IDR & ((unsigned int)1 << pin_number);
}


#if 0
static char gpio_pin_state(unsigned short);
#endif

#endif /* #ifndef GPIO_STM32F1_C */
