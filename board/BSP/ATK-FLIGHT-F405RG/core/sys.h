#ifndef __BASE_SYS_H_
#define __BASE_SYS_H_

#include <stdio.h>
#include <stdarg.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal.h>
#include <cachel1_armv7.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#define ARRAY_SIZE(array)   (sizeof(array) / sizeof(array[0]))

#define log_level(level, fmt, args...)  printf("["level"] %s:%d - " fmt"\r\n", __func__, __LINE__, ##args)
#define info(fmt, args...)              log_level("info", fmt, ##args)
#define warn(fmt, args...)              log_level("warn", fmt, ##args)
#define err(fmt, args...)               log_level("error", fmt, ##args)

extern void delay_us(unsigned int nus);
extern void delay_ms(unsigned int nms);
extern void delay_xms(unsigned int ms);
extern unsigned int systick_count(void);
extern void Error_Handler(void);
extern void system_init(void);

#endif /* __BASE_SYS_H_ */
