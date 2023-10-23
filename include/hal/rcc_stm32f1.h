/* passing non standard values (the values outside of the enumeration
 * associated with the function) is undefined
 */
#ifndef RCC_STM32F1_H
#define RCC_STM32F1_H

#define _RCC(X) ((volatile struct rcc *)(X))
#define RCC _RCC(0x40021000)


/* order of bits is how they appear in the rcc peripheral */

#define RCC_HSICAL_BEGIN 8
#define RCC_HSITRIM_BEGIN 3
#define RCC_SWS_BEGIN 2
#define RCC_HPRE_BEGIN 4
#define RCC_PRE1_BEGIN 8
#define RCC_PRE2_BEGIN 11
#define RCC_ADCPRE_BEGIN 14
#define RCC_PLLSRC_BIT 16
#define RCC_PLLXTPRE_BIT 17
#define RCC_PLLMUL_BEGIN 18
#define RCC_USBPRE_BIT 22
#define RCC_MCO_BEGIN 24

/* both _BV and 1UL << bit can be used with these */
enum RCC_CONTROL_BITS {
	RCC_CONTROL_HSION,
	RCC_CONTROL_HSIRDY,
	RCC_CONTROL_HSEON = 16,
	RCC_CONTROL_HSERDY,
	RCC_CONTROL_HSEBYP,
	RCC_CONTROL_CSSON,
	RCC_CONTROL_PLLON = 24,
	RCC_CONTROL_PLLRDY
};

enum RCC_CONF_SYSTEM_CLOCK {
	RCC_CONF_SW_HSI,
	RCC_CONF_SW_HSE,
	RCC_CONF_SW_PLL,
};

enum RCC_CONF_AHB_PRESCALER {
	RCC_AHB_PRESCALER_SYSCLK_DIV_1,
	RCC_AHB_PRESCALER_SYSCLK_DIV_2 = 0b1000,
	RCC_AHB_PRESCALER_SYSCLK_DIV_4,
	RCC_AHB_PRESCALER_SYSCLK_DIV_8,
	RCC_AHB_PRESCALER_SYSCLK_DIV_16,
	RCC_AHB_PRESCALER_SYSCLK_DIV_64,
	RCC_AHB_PRESCALER_SYSCLK_DIV_128,
	RCC_AHB_PRESCALER_SYSCLK_DIV_256,
	RCC_AHB_PRESCALER_SYSCLK_DIV_512
};

enum RCC_CONF_APB1_PRESCALER {
	RCC_APB1_PRESCALER_HCLK_DIV_1,
	RCC_APB1_PRESCALER_HCLK_DIV_2 = 0b100,
	RCC_APB1_PRESCALER_HCLK_DIV_4,
	RCC_APB1_PRESCALER_HCLK_DIV_8,
	RCC_APB1_PRESCALER_HCLK_DIV_16,
};

enum RCC_CONF_APB2_PRESCALER {
	RCC_APB2_PRESCALER_HCLK_DIV_1,
	RCC_APB2_PRESCALER_HCLK_DIV_2 = 0b100,
	RCC_APB2_PRESCALER_HCLK_DIV_4,
	RCC_APB2_PRESCALER_HCLK_DIV_8,
	RCC_APB2_PRESCALER_HCLK_DIV_16,
};

enum RCC_CONF_ADC_PRESCALER {
	RCC_ADC_PRESCALER_PCLK2_DIV_2,
	RCC_ADC_PRESCALER_PCLK2_DIV_4,
	RCC_ADC_PRESCALER_PCLK2_DIV_6,
	RCC_ADC_PRESCALER_PCLK2_DIV_8,
};

enum RCC_CONF_PLL_SRC {
	RCC_CONF_PLL_SRC_HSI_DIV_2,
	RCC_CONF_PLL_SRC_HSE
};

enum RCC_CONF_PLL_XTPRE {
	RCC_CONF_PLL_XTPRE_HSE,
	RCC_CONF_PLL_XTPRE_HSE_DIV_2
};

enum RCC_CONF_PLL_MUL {
	RCC_CONF_PLL_MUL_2,
	RCC_CONF_PLL_MUL_3,
	RCC_CONF_PLL_MUL_4,
	RCC_CONF_PLL_MUL_5,
	RCC_CONF_PLL_MUL_6,
	RCC_CONF_PLL_MUL_7,
	RCC_CONF_PLL_MUL_8,
	RCC_CONF_PLL_MUL_9,
	RCC_CONF_PLL_MUL_10,
	RCC_CONF_PLL_MUL_11,
	RCC_CONF_PLL_MUL_12,
	RCC_CONF_PLL_MUL_13,
	RCC_CONF_PLL_MUL_14,
	RCC_CONF_PLL_MUL_15,
	RCC_CONF_PLL_MUL_16
};

enum RCC_CONF_USB_PRESCALER {
	RCC_CONF_USB_PRESCALER_DIV_1_DOT_5,
	RCC_CONF_USB_PRESCALER_NO_DIV
};

enum RCC_CONF_MCO {
	RCC_MCO_NO_CLOCK,
	RCC_MCO_SYSCLK = 0b100,
	RCC_MCO_HSI,
	RCC_MCO_HSE,
	RCC_MCO_PLL_DIV2,
};

/*
 * do not use 1 << periph on these as they are encoded
 * use _BV because it get the periph number modulo 32
 */
enum RCC_PERIPH_ENABLE {
	/* AHB peripherals */
	RCC_DMA1EN = 0,
	RCC_DMA2EN,
	RCC_SRAMEN,
	RCC_FLITFEN = 4,
	RCC_CRCEN = 6,
	RCC_FSMCEN = 8,
	RCC_SDIOEN = 10,
	/* APB2 peripherals */
	RCC_AFIOEN = 32,
	RCC_IOPAEN = 32 + 2,
	RCC_IOPBEN,
	RCC_IOPCEN,
	RCC_IOPDEN,
	RCC_IOPEEN,
	RCC_IOPFEN,
	RCC_IOPGEN,
	RCC_ADC1EN,
	RCC_ADC2EN,
	RCC_TIM1EN,
	RCC_SPI1EN,
	RCC_TIM8EN,
	RCC_USART1EN,
	RCC_ADC3EN,
	RCC_TIM9EN = 32 + 19,
	RCC_TIM10EN,
	RCC_TIM11EN,
	/* APB1 peripherals */
	RCC_TIM2EN = 64,
	RCC_TIM3EN,
	RCC_TIM4EN,
	RCC_TIM5EN,
	RCC_TIM6EN,
	RCC_TIM7EN,
	RCC_TIM12EN,
	RCC_TIM13EN,
	RCC_TIM14EN,
	RCC_WWDGEN = 64 + 11,
	RCC_SPI2EN = 64 + 14,
	RCC_SPI3EN,
	RCC_USART2EN = 64 + 17,
	RCC_USART3EN,
	RCC_USART4EN,
	RCC_USART5EN,
	RCC_I2C1EN,
	RCC_I2C2EN,
	RCC_USBEN,
	RCC_CANEN = 64 + 25,
	RCC_BKPEN = 64 + 27,
	RCC_PWREN,
	RCC_DACEN
};

/*
 * do not use 1 << periph on these as they are encoded
 * use _BV because it get the periph number modulo 32
 */
enum RCC_PERIPH_RESET {
	/* APB2 peripherals */
	RCC_AFIORST = 0,
	RCC_IOPARST = 2,
	RCC_IOPBRST,
	RCC_IOPCRST,
	RCC_IOPDRST,
	RCC_IOPERST,
	RCC_IOPFRST,
	RCC_IOPGRST,
	RCC_ADC1RST,
	RCC_ADC2RST,
	RCC_TIM1RST,
	RCC_SPI1RST,
	RCC_TIM8RST,
	RCC_USART1RST,
	RCC_ADC3RST,
	RCC_TIM9RST = 19,
	RCC_TIM10RST,
	RCC_TIM11RST,
	/* APB1 peripherals */
	RCC_TIM2RST = 32 + 0,
	RCC_TIM3RST,
	RCC_TIM4RST,
	RCC_TIM5RST,
	RCC_TIM6RST,
	RCC_TIM7RST,
	RCC_TIM12RST,
	RCC_TIM13RST,
	RCC_TIM14RST,
	RCC_WWDGRST = 32 + 11,
	RCC_SPI2RST = 32 + 14,
	RCC_SPI3RST,
	RCC_USART2RST = 32 + 17,
	RCC_USART3RST,
	RCC_USART4RST,
	RCC_USART5RST,
	RCC_I2C1RST,
	RCC_I2C2RST,
	RCC_USBRST,
	RCC_CANRST = 32 + 25,
	RCC_BKPRST = 32 + 27,
	RCC_PWRRST,
	RCC_DACRST,
};

struct rcc {
	volatile unsigned int CR;
	volatile unsigned int CFGR;
	volatile unsigned int CIR;
	volatile unsigned int APB2RSTR;
	volatile unsigned int APB1RSTR;
	volatile unsigned int AHBENR;
	volatile unsigned int APB2ENR;
	volatile unsigned int APB1ENR;
	volatile unsigned int BDCR;
	volatile unsigned int CSR;
};

/* peripheral functions */
static void       	rcc_periph_enable(const unsigned char);
static void       	rcc_periph_reset(const unsigned char);
static void       	rcc_periph_disable(const unsigned char);
static char       	rcc_periph_state(const unsigned char);
static inline void	rcc_control_enable(const unsigned char);
static inline void	rcc_control_disable(const unsigned char);
static inline char	rcc_control_state(const unsigned char);
static inline char	rcc_control_get_hsical(void);
static void       	rcc_control_set_hsitrim(const unsigned char);
static inline char	rcc_control_get_hsitrim(void);
static void       	rcc_conf_system_clock(const unsigned char);
static inline char	rcc_system_clock_status(void);
static void       	rcc_conf_ahb_prescaler(const unsigned char);
static inline char	rcc_get_ahb_prescaler(void);
static void       	rcc_conf_apb1_prescaler(const unsigned char);
static inline char	rcc_get_apb1_prescaler(void);
static void       	rcc_conf_apb2_prescaler(const unsigned char);
static inline char	rcc_get_apb2_prescaler(void);
static void       	rcc_conf_adc_prescaler(const unsigned char);
static inline char	rcc_get_adc_prescaler(void);
static void       	rcc_conf_pll_src(const unsigned char);
static void       	rcc_conf_pll_xtpre(const unsigned char);
static void       	rcc_conf_pll_mul(const unsigned char);
static inline char	rcc_get_pll_mul(void);
static void       	rcc_conf_usb_prescaler(const unsigned char);
static void       	rcc_conf_mco(const unsigned char);
static inline char	rcc_get_mco(void);

#include "rcc_stm32f1.c"

#endif /* #ifndef RCC_STM32F1_H */
