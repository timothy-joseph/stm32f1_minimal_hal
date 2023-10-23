/* pin notation encodes the bank number and pin number into a single
 * unsigned short (2 byte) variable. this can be used to achieve a more
 * arduino-like feeling
 *
 * the gpio_pin functions call their corresponding normal gpio functions
 * after decoding, so it might mean that using the normal gpio functions
 * will make your program faster, but also smaller
 *
 * the advantage of the pin notation is that you can do something like
 * const unsigned short led_pin = PIN('C', 13);
 * or
 * #define LED_PIN PIN('C', 13)
 * in your program
 */
#ifndef GPIO_STM32F1_H
#define GPIO_STM32F1_H

#include "reg.h"

#define GPIO(X) ((struct gpio *)((X)))
#define GPIO_FROM_OFFSET_FROM_A(X) GPIO(0x40010800 + 0x400 * (X))
#define GPIOA GPIO(0x40010800)
#define GPIOB GPIO(0x40010C00)
#define GPIOC GPIO(0x40011000)
#define GPIOD GPIO(0x40011400)
#define GPIOE GPIO(0x40011800)
#define GPIOF GPIO(0x40011C00)
#define GPIOG GPIO(0x40012000)
#define GPIOX_IN_RANGE(GPIOX) \
         ((GPIOX) != NULL && (GPIOX) >= GPIOA && (GPIOX) <= GPIOG)

/* BANK is to be specified as a char between 'A' and 'G' for all of the
 * following macros
 */
#define PIN(BANK, PIN_NUM) (((unsigned short)((BANK)) << 8) | (PIN_NUM))
#define PIN_BANK(PIN_NOTATION) ((unsigned char)(((PIN_NOTATION) >> 8) & 0xFF))
#define PIN_NUMBER(PIN_NOTATION) ((unsigned char)((PIN_NOTATION) & 0xFF))
#define GPIO_FROM_BANK(BANK) GPIO_FROM_OFFSET_FROM_A((BANK) - 'A')


enum {
	GPIO_MODE_INPUT = 0,
	GPIO_MODE_OUTPUT_10_MHZ,
	GPIO_MODE_OUTPUT_2_MHZ,
	GPIO_MODE_OUTPUT_50_MHZ
};

enum {
	GPIO_CNF_INPUT_ANALOG = 0,
	GPIO_CNF_INPUT_FLOATING,
	GPIO_CNF_INPUT_PULL_UP_DOWN,
};

enum {
	GPIO_CNF_OUTPUT_PUSH_PULL = 0,
	GPIO_CNF_OUTPUT_OPEN_DRAIN,
	GPIO_CNF_ALT_OUTPUT_PUSH_PULL,
	GPIO_CNF_ALT_OUTPUT_OPEN_DRAIN,
};

struct gpio {
	volatile unsigned int CRL;
	volatile unsigned int CRH;
	volatile unsigned int IDR;
	volatile unsigned int ODR;
	volatile unsigned int BSRR;
	volatile unsigned int BRR;
	volatile unsigned int LCKR;
};

static void	gpio_set_mode(struct gpio *, unsigned char, char);
static void	gpio_set_cnf(struct gpio *, unsigned char, char);
static void	gpio_pin_set_mode(unsigned short, char);
static void	gpio_pin_set_cnf(unsigned short, char);
static char	gpio_get_mode(struct gpio *, unsigned char);
static char	gpio_get_cnf(struct gpio *, unsigned char);
static char	gpio_pin_get_mode(unsigned short);
static char	gpio_pin_get_cnf(unsigned short);
static void	gpio_set_pin(struct gpio *, unsigned char);
static void	gpio_clear_pin(struct gpio *, unsigned char);
static void	gpio_toggle_pin(struct gpio *, unsigned char);
static void	gpio_pin_set_pin(unsigned short);
static void	gpio_pin_clear_pin(unsigned short);
static void	gpio_pin_toggle_pin(unsigned short);
static char	gpio_state(struct gpio *, unsigned char);
static char	gpio_pin_state(unsigned short);

#include "gpio_stm32f1.c"

#endif /* #ifndef GPIO_STM32F1_H */
