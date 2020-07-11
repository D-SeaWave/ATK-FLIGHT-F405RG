#ifndef __BSP_ATK_FLIGHT_F405RG_DRIVER_MPU6000_H__
#define __BSP_ATK_FLIGHT_F405RG_DRIVER_MPU6000_H__

#include <maths.h>

/* after spi_init */
extern void mpu6000_init(void);

extern void mpu6000_read_gyyro(hvector3d_t *acc);
extern void mpu6000_read_acc(hvector3d_t *acc);

#endif /* __BSP_ATK_FLIGHT_F405RG_DRIVER_MPU6000_H__ */
