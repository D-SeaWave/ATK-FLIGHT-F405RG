#ifndef __BSP_ATK_FLIGHT_F405RG_SPI_H__
#define __BSP_ATK_FLIGHT_F405RG_SPI_H__

#include <stdbool.h>

extern void spi_init(void);

extern bool spi_transmitreceive(const unsigned int index, void *txbuf, void *rxbuf,
        const uint16_t size, const unsigned int timeout);

#endif /* __BSP_ATK_FLIGHT_F405RG_SPI_H__ */
