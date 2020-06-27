#include <core/sys.h>
#include <periph/usart-uart.h>

static UART_HandleTypeDef huart[] = {
    {
        .Instance = USART1,
    }, {
        .Instance = USART2,
    }, {
        .Instance = USART3,
    }, {
        .Instance = UART4,
    }, {
        .Instance = UART5,
    }
};

static void uart_init_cb(const unsigned int index, const unsigned int baudrate)
{
    if (index >= ARRAY_SIZE(huart)) {
        Error_Handler();
    }

    huart[index].Init.BaudRate   = baudrate;
    huart[index].Init.WordLength = UART_WORDLENGTH_8B;
    huart[index].Init.StopBits   = UART_STOPBITS_1;
    huart[index].Init.Parity     = UART_PARITY_NONE;
    huart[index].Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    huart[index].Init.Mode       = UART_MODE_TX_RX;
    huart[index].gState          = HAL_UART_STATE_RESET;
    HAL_UART_Init(&huart[index]);
    __HAL_UART_DISABLE_IT(&huart[index], UART_IT_RXNE);
    __HAL_UART_DISABLE_IT(&huart[index], UART_IT_TXE);
}

void uart_sendc_sync(const unsigned int index, char ch)
{
    uart_send_sync(index, &ch, 1);
}

void uart_send_sync(const unsigned int index, void *restrict buf, const unsigned int len)
{
    char *c_ptr;
    unsigned int i;
    volatile USART_TypeDef *uart;

    if (index >= ARRAY_SIZE(huart)) {
        Error_Handler();
    }

    uart = huart[index].Instance;
    for (c_ptr = buf, i = 0; i < len; ++i) {
        while (!(uart->SR & 0x40)) {
            continue;
        }
    
        uart->SR = 0;
        uart->DR = c_ptr[i];
    }
}

void uart_init(void)
{
    uart_init_cb(0, 115200);
    uart_init_cb(1, 115200);
    uart_init_cb(2, 115200);
    uart_init_cb(3, 115200);
    uart_init_cb(4, 115200);
}

