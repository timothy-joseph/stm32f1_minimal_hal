#ifndef RCC_STM32F1_C
#define RCC_STM32F1_C

#include "common.h"
#include "rcc_stm32f1.h"

/* enables a peripheral
 * uses the enable registers and RCC_periphEN notation
 * associated enum: RCC_PERIPH_ENABLE
 * do not use 1 << periph on these as they are encoded
 * use _BV because it get the periph number modulo 32
 */
static void
rcc_periph_enable(const unsigned char periph)
{
	switch (periph / 32) {
	case 0:
		RCC->AHBENR |= _BV(periph % 32);
		break;
	case 1:
		RCC->APB2ENR |= _BV(periph % 32);
		break;
	case 2:
		RCC->APB1ENR |= _BV(periph % 32);
		break;
	}
}

/* disables a peripheral
 * uses the reset register (RCC_APB2RSTR, RCC_APB1RSTR) and RCC_periphRST
 * notation
 * associated enum: RCC_PERIPH_RESET
 * do not use _BV on these as they are encoded
 */
static void
rcc_periph_reset(const unsigned char periph)
{
	switch (periph / 32) {
	case 0:
		RCC->APB2RSTR |= _BV(periph % 32);
		break;
	case 1:
		RCC->APB1RSTR |= _BV(periph % 32);
		break;
	}
}

/* gets the state of a peripheral
 * uses the enable registers and RCC_periphEN notation
 * associated enum: RCC_PERIPH_ENABLE
 * do not use 1 << periph on these as they are encoded
 * use _BV because it get the periph number modulo 32
 */
static char
rcc_periph_state(const unsigned char periph)
{
	switch (periph / 32) {
	case 0:
		return (RCC->AHBENR >> (periph % 32)) & 1;
	case 1:
		return (RCC->APB2ENR >> (periph % 32)) & 1;
	case 2:
		return (RCC->APB1ENR >> (periph % 32)) & 1;
	}
}


/* same effect as rcc_reset_periph, but uses the enable registers (RCC_AHBENR,
 * RCC_APB2ENR, RCC_APB1ENR) and RCC_periphEN notation
 * associated enum: RCC_PERIPH_ENABLE
 * do not use _BV on these as they are encoded
 */
static void
rcc_periph_disable(const unsigned char periph)
{
	switch (periph / 32) {
	case 0:
		RCC->AHBENR &= ~(_BV(periph % 32));
		break;
	case 1:
		RCC->APB2ENR &= ~(_BV(periph % 32));
		break;
	case 2:
		RCC->APB1ENR &= ~(_BV(periph % 32));
		break;
	}
}


/* used to enable a single clock control, the bit number must be passed
 * uses the control register RCC_CR register and RCC_CONTROL_control
 * notation
 * associated enum: RCC_CONTROL_BITS
 * multiple bits can be enabled in a instruction by doing something like
 * RCC->CR |= _BV(RCC_CONTROL_HSION) | _BV(RCC_CONTROL_PLLON);
 */
static inline void
rcc_control_enable(const unsigned char bit)
{
	RCC->CR |= _BV(bit);
}

/* used to disable a single clock control, the bit number must be passed
 * uses the control register RCC_CR register and RCC_CONTROL_control
 * notation
 * associated enum: RCC_CONTROL_BITS
 * multiple bits can be disabled in a instruction by doing something like
 * RCC->CR &= ~(_BV(RCC_CONTROL_HSION) | _BV(RCC_CONTROL_PLLON));
 */
static inline void
rcc_control_disable(const unsigned char bit)
{
	RCC->CR &= ~(_BV(bit));
}


/* used to get the state single clock control, the bit number must be passed
 * uses the control register RCC_CR register and RCC_CONTROL_control
 * notation
 * associated enum: RCC_CONTROL_BITS
 */
static inline char
rcc_control_state(const unsigned char bit)
{
	return (RCC->CR >> bit) & 1;
}

/* used to get the value of the hardware hsi calibration */
static inline char
rcc_control_get_hsical(void)
{
	return (RCC->CR >> RCC_HSICAL_BEGIN) & 0xFF;
}

/* used to set the value of the hsi trim
 * value must be between 0 and 16
 */
static void
rcc_control_set_hsitrim(const unsigned char val)
{
	if (val > 0xF)
		return;
	RCC->CR &= ~(0xF << RCC_HSITRIM_BEGIN);
	RCC->CR |= val << RCC_HSITRIM_BEGIN;
}

/* used to get the value of hsi trim */
static inline char
rcc_control_get_hsitrim(void)
{
	return (RCC->CR >> RCC_HSITRIM_BEGIN) & 0xF;
}


static void
rcc_conf_system_clock(const unsigned char conf)
{
	if (conf > 2)
		return;
	RCC->CFGR &= ~3UL;
	RCC->CFGR |= conf;
}

static inline char
rcc_system_clock_status(void)
{
	return (RCC->CFGR >> RCC_SWS_BEGIN) & 3UL;
}


static void
rcc_conf_ahb_prescaler(const unsigned char conf)
{
	if (conf > 15)
		return;
	RCC->CFGR &= ~(0xF << RCC_HPRE_BEGIN);
	RCC->CFGR |= conf << RCC_HPRE_BEGIN;
}

static inline char
rcc_get_ahb_prescaler(void)
{
	return (RCC->CFGR >> RCC_HSICAL_BEGIN) & 0xF;
}

static void
rcc_conf_apb1_prescaler(const unsigned char conf)
{
	if (conf > 7)
		return;
	RCC->CFGR &= ~(7UL << RCC_PRE1_BEGIN);
	RCC->CFGR |= conf << RCC_PRE1_BEGIN;
}

static inline char
rcc_get_apb1_prescaler(void)
{
	return (RCC->CFGR >> RCC_PRE1_BEGIN) & 7;
}

static void
rcc_conf_apb2_prescaler(const unsigned char conf)
{
	if (conf > 7)
		return;
	RCC->CFGR &= ~(7UL << RCC_PRE2_BEGIN);
	RCC->CFGR |= conf << RCC_PRE2_BEGIN;
}

static inline char
rcc_get_apb2_prescaler(void)
{
	return (RCC->CFGR >> RCC_PRE2_BEGIN) & 7;
}

static void
rcc_conf_adc_prescaler(const unsigned char conf)
{
	if (conf > 3)
		return;
	RCC->CFGR &= ~(3UL << RCC_ADCPRE_BEGIN);
	RCC->CFGR |= conf << RCC_ADCPRE_BEGIN;
}

static inline char
rcc_get_adc_prescaler(void)
{
	return (RCC->CFGR >> RCC_ADCPRE_BEGIN) & 3;
}

static void
rcc_conf_pll_src(const unsigned char conf)
{
	if (conf == RCC_CONF_PLL_SRC_HSI_DIV_2)
		RCC->CFGR &= ~(_BV(RCC_PLLSRC_BIT));
	else
		RCC->CFGR |= _BV(RCC_PLLSRC_BIT);
}

static void
rcc_conf_pll_xtpre(const unsigned char conf)
{
	if (conf == RCC_CONF_PLL_XTPRE_HSE)
		RCC->CFGR &= ~(_BV(RCC_PLLXTPRE_BIT));
	else
		RCC->CFGR |= _BV(RCC_PLLXTPRE_BIT);
}

static void
rcc_conf_pll_mul(const unsigned char conf)
{
	if (conf > 15)
		return;
	RCC->CFGR &= ~(0xF << RCC_PLLMUL_BEGIN);
	RCC->CFGR |= conf << RCC_PLLMUL_BEGIN;
}

static inline char
rcc_get_pll_mul(void)
{
	return (RCC->CFGR >> RCC_PLLMUL_BEGIN) & 0xF;
}

static void
rcc_conf_usb_prescaler(const unsigned char conf)
{
	if (conf == RCC_CONF_USB_PRESCALER_DIV_1_DOT_5)
		RCC->CFGR &= ~(_BV(RCC_USBPRE_BIT));
	else
		RCC->CFGR |= _BV(RCC_USBPRE_BIT);
}

static void
rcc_conf_mco(const unsigned char conf)
{
	if (conf > 7)
		return;
	RCC->CFGR &= ~(7UL << RCC_MCO_BEGIN);
	RCC->CFGR |= conf << RCC_MCO_BEGIN;
}

static inline char
rcc_get_mco(void)
{
	return (RCC->CFGR >> RCC_MCO_BEGIN) & 7;
}

#endif /* #ifndef RCC_STM32F1_C */
