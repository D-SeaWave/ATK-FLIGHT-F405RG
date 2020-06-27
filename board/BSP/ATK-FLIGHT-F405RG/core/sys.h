#ifndef __BASE_SYS_H_
#define __BASE_SYS_H_

#include <stm32f4xx.h>
#include <stm32f4xx_hal.h>
#include <cachel1_armv7.h>

#define ARRAY_SIZE(array)   (sizeof(array) / sizeof(array[0]))

extern void delay_us(unsigned int nus);
extern void delay_ms(unsigned int nms);
extern void delay_xms(unsigned int ms);
extern unsigned int systick_count(void);
extern void Error_Handler(void);
extern void system_init(void);

#endif /* __BASE_SYS_H_ */
