#ifndef EXTI_STM32F1_H
#define EXTI_STM32F1_H

#include "exti_stm32f1.h"

static void
enable_exti(const unsigned char exti)
{
	EXTI->IMR |= 1UL << exti;
	EXTI->EMR |= 1UL << exti;
}

static void
enable_rising_exti(const unsigned char exti)
{
	EXTI->RTSR |= 1UL << exti;
}

static void
enable_falling_exti(const unsigned char exti)
{
	EXTI->FTSR |= 1UL << exti;
}


static void
software_exti(const unsigned char exti)
{
	EXTI->SWIER |= 1UL << exti;
}

static void
clear_pending_exti(const unsigned char exti)
{
	EXTI->PR |= 1UL << exti;
}

static char
is_pending_exti(const unsigned char exti)
{
	return !!(EXTI->PR & (1UL << exti));
}

static void
disable_exti(const unsigned char exti)
{
	EXTI->IMR &= ~(1UL << exti);
	EXTI->EMR &= ~(1UL << exti);
}

static void
disable_rising_exti(const unsigned char exti)
{
	EXTI->RTSR &= ~(1UL << exti);
}

static void
disable_falling_exti(const unsigned char exti)
{
	EXTI->FTSR &= ~(1UL << exti);
}

#endif
