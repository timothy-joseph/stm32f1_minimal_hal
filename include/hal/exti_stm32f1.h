#ifndef EXTI_STM32F1_H
#define EXTI_STM32F1_h

#define _EXTI(X) ((volatile struct exti *)(X))
#define EXTI _EXTI(0x40010400)

enum EXTIn {
	EXTI0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	EXTI5,
	EXTI6,
	EXTI7,
	EXTI8,
	EXTI9,
	EXTI10,
	EXTI11,
	EXTI12,
	EXTI13,
	EXTI14,
	EXTI15,
	EXTI16,
	EXTI17,
	EXTI18,
};

struct exti {
	volatile unsigned int IMR;
	volatile unsigned int EMR;
	volatile unsigned int RTSR;
	volatile unsigned int FTSR;
	volatile unsigned int SWIER;
	volatile unsigned int PR;
};

static void enable_exti(const unsigned char);
static void enable_falling_exti(const unsigned char);
static void enable_rising_exti(const unsigned char);
static void enable_software_exti(const unsigned char);
static void clear_pending_exti(const unsigned char);
static char is_pending_exti(const unsigned char);
static void disable_exti(const unsigned char);
static void disable_rising_exti(const unsigned char);
static void disable_falling_exti(const unsigned char);

#include "exti_stm32f1.c"

#endif /* exti_stm32f1.h */
