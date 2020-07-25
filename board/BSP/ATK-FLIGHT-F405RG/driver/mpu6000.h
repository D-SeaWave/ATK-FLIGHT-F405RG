#ifndef __BSP_ATK_FLIGHT_F405RG_DRIVER_MPU6000_H__
#define __BSP_ATK_FLIGHT_F405RG_DRIVER_MPU6000_H__

#include <maths.h>

typedef struct {
    hvector3d_t gyro;
    hvector3d_t acc;
    uint32_t    timestamp;
} mpu6000_data_t;

/* after spi_init */
extern void mpu6000_init(void);

extern int mpu6000_receive_data(mpu6000_data_t *data);

#endif /* __BSP_ATK_FLIGHT_F405RG_DRIVER_MPU6000_H__ */
