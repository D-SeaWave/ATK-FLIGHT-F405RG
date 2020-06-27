#include <core/sys.h>
#include <periph/usart-uart.h>

void _ttywrch(int ch)
{
    uart_sendc_sync(0, ch);
}

int _read(int fd, char *ptr, int len)
{
    return len;
}

int _write(int fd, char *ptr, int len)
{
    uart_send_sync(0, ptr, len);

    return len;
}
