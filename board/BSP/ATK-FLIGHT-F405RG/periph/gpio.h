#ifndef __BSP_ATK_FLIGHT_F405RG_GPIO_H__
#define __BSP_ATK_FLIGHT_F405RG_GPIO_H__

#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>

typedef struct {
	GPIO_TypeDef *gpio;
	unsigned int  pin;
} single_gpio_pin_t;

static inline void gpio_set_pin(GPIO_TypeDef *restrict GPIO, const uint16_t pin)
{
    GPIO->BSRR = (uint32_t)pin;
}

static inline void gpio_reset_pin(GPIO_TypeDef *restrict GPIO, const uint16_t pin)
{
    GPIO->BSRR = (uint32_t)pin << 16;
}

extern void gpio_switch_io_mode(GPIO_TypeDef *restrict GPIO, const uint16_t pin,
        const uint8_t mode);

#endif /* __BSP_ATK_FLIGHT_F405RG_GPIO_H__ */
