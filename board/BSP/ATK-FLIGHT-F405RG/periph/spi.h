#ifndef __BSP_ATK_FLIGHT_F405RG_SPI_H__
#define __BSP_ATK_FLIGHT_F405RG_SPI_H__

#include <stdbool.h>

extern void spi_init(void);
extern void spi_set_speed(const unsigned int index, const unsigned int speed);

extern bool spi_transmitreceive(const unsigned int index, void *txbuf, void *rxbuf,
    const uint16_t size, const unsigned int timeout);

static inline bool spi_transmit(const unsigned int index, void *buf, const uint16_t size,
        const unsigned int timeout)
{
    return spi_transmitreceive(index, buf, NULL, size, timeout);
}

static inline bool spi_receive(const unsigned int index, void *buf, const uint16_t size,
        const unsigned int timeout)
{
    return spi_transmitreceive(index, NULL, buf, size, timeout);
}

#endif /* __BSP_ATK_FLIGHT_F405RG_SPI_H__ */
