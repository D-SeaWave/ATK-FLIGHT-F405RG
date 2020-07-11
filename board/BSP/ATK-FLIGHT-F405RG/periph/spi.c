#include <core/sys.h>
#include <periph/spi.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_spi.h>

static SPI_HandleTypeDef hspi[] = {
    {
        .Instance = SPI1,
    },
    {
        .Instance = SPI2,
    },
    {
        .Instance = SPI3,
    },
};

static void spi_init_cb(const unsigned int index)
{
    SPI_HandleTypeDef *const h =  &hspi[index];

    h->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    h->Init.CLKPhase          = SPI_PHASE_2EDGE;
    h->Init.CLKPolarity       = SPI_POLARITY_HIGH;
    h->Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
    h->Init.CRCPolynomial     = 7;
    h->Init.DataSize          = SPI_DATASIZE_8BIT;
    h->Init.Direction         = SPI_DIRECTION_2LINES;
    h->Init.FirstBit          = SPI_FIRSTBIT_MSB;
    h->Init.TIMode            = SPI_TIMODE_DISABLE;
    h->Init.NSS               = SPI_NSS_SOFT;
    h->Init.Mode              = SPI_MODE_MASTER;
    if (HAL_SPI_Init(h) != HAL_OK) {
        Error_Handler();
    }
    __HAL_SPI_ENABLE(h);
}

void spi_init(void)
{
    spi_init_cb(0);
    spi_init_cb(1);
    spi_init_cb(2);
}

void spi_set_speed(const unsigned int index, const unsigned int speed)
{
    SPI_HandleTypeDef *const h =  &hspi[index];

    if (index >= ARRAY_SIZE(hspi)) {
        Error_Handler();
    }

    __HAL_SPI_DISABLE(h);
    h->Instance->CR1 &= 0xFFC7;
    h->Instance->CR1 |= speed;
    __HAL_SPI_ENABLE(h);
}

bool spi_transmitreceive(const unsigned int index, void *txbuf, void *rxbuf,
    const uint16_t size, const unsigned int timeout)
{
    return (HAL_SPI_TransmitReceive(&hspi[index], txbuf, rxbuf, size, timeout) == HAL_OK);
}
