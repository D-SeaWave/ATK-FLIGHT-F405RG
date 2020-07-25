#include <core/sys.h>
#include <periph/gpio.h>
#include <periph/pinmux.h>
#include <stm32f4xx_hal_cortex.h>

static void periph_clock_enable(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_USART3_CLK_ENABLE();
    __HAL_RCC_UART4_CLK_ENABLE();
    __HAL_RCC_UART5_CLK_ENABLE();
    __HAL_RCC_USART6_CLK_DISABLE();

    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_SPI3_CLK_ENABLE();

    __HAL_RCC_TIM3_CLK_ENABLE();
    /*
    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
     */
}

static void enable_interrupt(IRQn_Type irq, uint32_t preempt_pri, uint32_t subpri)
{
    HAL_NVIC_EnableIRQ(irq);
    HAL_NVIC_SetPriority(irq, preempt_pri, subpri);
}

static inline void external_line_interrupt_config(void)
{
    enable_interrupt(EXTI3_IRQn, 4, 4);
}

void periph_interrupt_config(void)
{
    enable_interrupt(USART1_IRQn, 3, 3);
    enable_interrupt(USART2_IRQn, 3, 3);
    enable_interrupt(USART3_IRQn, 3, 3);
    enable_interrupt(UART4_IRQn, 3, 3);
    enable_interrupt(UART5_IRQn, 3, 3);
    /*
    enable_interrupt(SPI1_IRQn, 0, 1);
    enable_interrupt(SPI2_IRQn, 0, 1);
    enable_interrupt(SPI3_IRQn, 0, 1);
     */
    external_line_interrupt_config();
}

void pinmux_init(void)
{
    GPIO_InitTypeDef gpio;

    periph_clock_enable();
    gpio.Pull = GPIO_NOPULL;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Speed = GPIO_SPEED_FAST;

    /* USART1 */
    gpio.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    gpio.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* USART2 */
    gpio.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    gpio.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* USART3 */
    gpio.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    gpio.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOC, &gpio);

    /* UART4 */
    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* UART5 TX */
    gpio.Pin = GPIO_PIN_12;
    gpio.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOC, &gpio);

    /* UART5 RX */
    gpio.Pin = GPIO_PIN_2;
    gpio.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOD, &gpio);

    /* SPI1 */
    gpio.Pull = GPIO_PULLUP;
    //gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    gpio.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* SPI2 */
    gpio.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &gpio);

    /* SPI3 */
    gpio.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    gpio.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(GPIOB, &gpio);

    /* TIM3 */
    gpio.Speed = GPIO_SPEED_FAST;
    gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    gpio.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOC, &gpio);

#if 0
    /* USB OTG FS */
    gpio.Pin = GPIO_PIN_11 | GPIO_PIN_12;
    gpio.Alternate = GPIO_AF10_OTG_FS;
    HAL_GPIO_Init(GPIOA, &gpio);
#endif

    /* 普通GPIO口初始化 */
    gpio.Alternate = 0;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;

    /* SPI1 CS - MPU9250 */
    gpio.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOC, &gpio);

    /* SPI2 CS - SD */
    gpio.Pin = GPIO_PIN_1;
    HAL_GPIO_Init(GPIOC, &gpio);

    /* SPI3 CS - AT7456 */
    gpio.Pin = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOB, &gpio);

    /* I2C - GPIO I2C */
    gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOB, &gpio);

    /* LED Strip */
    gpio.Pin = GPIO_PIN_15;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* LED 0, BLUE LED */
    gpio.Pin = GPIO_PIN_9;
    HAL_GPIO_Init(GPIOB, &gpio);

    /* LED 1, RED LED */
    /* gpio.Pin = GPIO_PIN_14;
    HAL_GPIO_Init(GPIOA, &gpio); */

    /* BEEPER */
    gpio.Pin = GPIO_PIN_13;
    HAL_GPIO_Init(GPIOC, &gpio);

    /* EXT INT - MPU9250 */
    gpio.Pin = GPIO_PIN_3;
    gpio.Mode = GPIO_MODE_IT_RISING;
    gpio.Alternate = GPIO_AF15_EVENTOUT;
    gpio.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOC, &gpio);
}
