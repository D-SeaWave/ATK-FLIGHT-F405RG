#include <core/sys.h>
#include <periph/spi.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_spi.h>

static SPI_HandleTypeDef hspi[3] = {0};

static void spi_init_cb(const unsigned int index)
{
    SPI_HandleTypeDef *const h =  &hspi[index];
    SPI_TypeDef *const instance[] = {SPI1, SPI2, SPI3};

    h->Instance               = instance[index];
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

    __HAL_SPI_DISABLE(h);
    h->Instance->CR1 &= 0xFFC7;
    h->Instance->CR1 |= speed;
    __HAL_SPI_ENABLE(h);
}

bool spi_transmitreceive(const unsigned int index, void *txbuf, void *rxbuf,
    const uint16_t size, const unsigned int timeout)
{
    if (HAL_SPI_TransmitReceive(&hspi[index], txbuf, rxbuf, size, timeout) != HAL_OK) {
       Error_Handler();
    }
    return true;
}

bool spi_receive(const unsigned int index, void *rxbuf, const uint16_t size, const unsigned int timeout)
{
    if (HAL_SPI_Receive(&hspi[index], rxbuf, size, timeout) != HAL_OK) {
        Error_Handler();
    }

    return true;
}

bool spi_transmit(const unsigned int index, void *txbuf, const uint16_t size, const unsigned int timeout)
{
    if (HAL_SPI_Transmit(&hspi[index], txbuf, size, timeout) != HAL_OK) {
        Error_Handler();
    }

    return true;
}

void SPI1_IRQHandler(void)
{
    HAL_SPI_IRQHandler(&hspi[0]);
}
