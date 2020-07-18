#ifndef __BSP_ATK_FLIGHT_F405RG_SPI_H__
#define __BSP_ATK_FLIGHT_F405RG_SPI_H__

#include <stdbool.h>

extern void spi_init(void);
extern void spi_set_speed(const unsigned int index, const unsigned int speed);

extern bool spi_transmitreceive(const unsigned int index, void *txbuf, void *rxbuf,
        const uint16_t size, const unsigned int timeout);

extern bool spi_receive(const unsigned int index, void *rxbuf, const uint16_t size,
        const unsigned int timeout);

extern bool spi_transmit(const unsigned int index, void *txbuf, const uint16_t size,
        const unsigned int timeout);

#endif /* __BSP_ATK_FLIGHT_F405RG_SPI_H__ */
