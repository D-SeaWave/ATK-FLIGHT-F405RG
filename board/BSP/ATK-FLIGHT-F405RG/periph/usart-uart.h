#ifndef __BOARD_BSP_ATK_FLIGHT_F405RG_PERIPH_USART_UART_H__
#define __BOARD_BSP_ATK_FLIGHT_F405RG_PERIPH_USART_UART_H__

extern void uart_init(void);

extern void uart_sendc_sync(const unsigned int index, char ch);

extern void uart_send_sync(const unsigned int index, void *restrict buf, const unsigned int len);

#endif /* __BOARD_BSP_ATK_FLIGHT_F405RG_PERIPH_USART_UART_H__ */
