#include <core/sys.h>
#include <periph/spi.h>
#include <periph/gpio.h>
#include <driver/mpu6000.h>

/* Registers of mpu6000 */
#define MPU_SELF_TEST_X_GYRO        0x00
#define MPU_SELF_TEST_Y_GYRO        0x01
#define MPU_SELF_TEST_Z_GYRO        0x02
#define MPU_SELF_TEST_X_ACCEL       0x0D
#define MPU_SELF_TEST_Y_ACCEL       0x0E
#define MPU_SELF_TEST_Z_ACCEL       0x0F
#define MPU_XG_OFFSET_H             0x13
#define MPU_XG_OFFSET_L             0x14
#define MPU_YG_OFFSET_H             0x15
#define MPU_YG_OFFSET_L             0x16
#define MPU_ZG_OFFSET_H             0x17
#define MPU_ZG_OFFSET_L             0x18
#define MPU_SMPLRT_DIV              0x19
#define MPU_CONFIG                  0x1A
#define MPU_GYRO_CONFIG             0x1B
#define MPU_ACCEL_CONFIG            0x1C
#define MPU_ACCEL_CONFIG2           0x1D
#define MPU_LP_ACCEL_ODR            0x1E
#define MPU_WOM_THR                 0x1F
#define MPU_FIFO_EN                 0x23
#define MPU_I2C_MST_CTRL            0x24
#define MPU_I2C_SLV0_ADDR           0x25
#define MPU_I2C_SLV0_REG            0x26
#define MPU_I2C_SLV0_CTRL           0x27
#define MPU_I2C_SLV1_ADDR           0x28
#define MPU_I2C_SLV1_REG            0x29
#define MPU_I2C_SLV1_CTRL           0x2A
#define MPU_I2C_SLV2_ADDR           0x2B
#define MPU_I2C_SLV2_REG            0x2C
#define MPU_I2C_SLV2_CTRL           0x2D
#define MPU_I2C_SLV3_ADDR           0x2E
#define MPU_I2C_SLV3_REG            0x2F
#define MPU_I2C_SLV3_CTRL           0x30
#define MPU_I2C_SLV4_ADDR           0x31
#define MPU_I2C_SLV4_REG            0x32
#define MPU_I2C_SLV4_DO             0x33
#define MPU_I2C_SLV4_CTRL           0x34
#define MPU_I2C_SLV4_DI             0x35
#define MPU_I2C_MST_STATUS          0x36
#define MPU_INT_PIN_CFG             0x37
#define MPU_INT_ENABLE              0x38
#define MPU_INT_STATUS              0x3A
#define MPU_ACCEL_XOUT_H            0x3B
#define MPU_ACCEL_XOUT_L            0x3C
#define MPU_ACCEL_YOUT_H            0x3D
#define MPU_ACCEL_YOUT_L            0x3E
#define MPU_ACCEL_ZOUT_H            0x3F
#define MPU_ACCEL_ZOUT_L            0x40
#define MPU_TEMP_OUT_H              0x41
#define MPU_TEMP_OUT_L              0x42
#define MPU_GYRO_XOUT_H             0x43
#define MPU_GYRO_XOUT_L             0x44
#define MPU_GYRO_YOUT_H             0x45
#define MPU_GYRO_YOUT_L             0x46
#define MPU_GYRO_ZOUT_H             0x47
#define MPU_GYRO_ZOUT_L             0x48
#define MPU_EXT_SENS_DATA_00        0x49
#define MPU_EXT_SENS_DATA_01        0x4A
#define MPU_EXT_SENS_DATA_02        0x4B
#define MPU_EXT_SENS_DATA_03        0x4C
#define MPU_EXT_SENS_DATA_04        0x4D
#define MPU_EXT_SENS_DATA_05        0x4E
#define MPU_EXT_SENS_DATA_06        0x4F
#define MPU_EXT_SENS_DATA_07        0x50
#define MPU_EXT_SENS_DATA_08        0x51
#define MPU_EXT_SENS_DATA_09        0x52
#define MPU_EXT_SENS_DATA_10        0x53
#define MPU_EXT_SENS_DATA_11        0x54
#define MPU_EXT_SENS_DATA_12        0x55
#define MPU_EXT_SENS_DATA_13        0x56
#define MPU_EXT_SENS_DATA_14        0x57
#define MPU_EXT_SENS_DATA_15        0x58
#define MPU_EXT_SENS_DATA_16        0x59
#define MPU_EXT_SENS_DATA_17        0x5A
#define MPU_EXT_SENS_DATA_18        0x5B
#define MPU_EXT_SENS_DATA_19        0x5C
#define MPU_EXT_SENS_DATA_20        0x5D
#define MPU_EXT_SENS_DATA_21        0x5E
#define MPU_EXT_SENS_DATA_22        0x5F
#define MPU_EXT_SENS_DATA_23        0x60
#define MPU_I2C_SLV0_DO             0x63
#define MPU_I2C_SLV1_DO             0x64
#define MPU_I2C_SLV2_DO             0x65
#define MPU_I2C_SLV3_DO             0x66
#define MPU_I2C_MST_DELAY_CTRL      0x67
#define MPU_SIGNAL_PATH_RESET       0x68
#define MPU_MOT_DETECT_CTRL         0x69
#define MPU_USER_CTRL               0x6A
#define MPU_PWR_MGMT1               0x6B
#define MPU_PWR_MGMT2               0x6C
#define MPU_FIFO_COUNTH             0x72
#define MPU_FIFO_COUNTL             0x73
#define MPU_FIFO_R_W                0x74
#define MPU_WHO_AM_I                0x75
#define MPU_XA_OFFSET_H             0x77
#define MPU_XA_OFFSET_L             0x78
#define MPU_YA_OFFSET_H             0x7A
#define MPU_YA_OFFSET_L             0x7B
#define MPU_ZA_OFFSET_H             0x7D
#define MPU_ZA_OFFSET_L             0x7E

#define AK8963_REG_WIA              0x00    /* Device ID */
#define AK8963_REG_INFO             0x01    /* Information */
#define AK8963_REG_ST1              0x02    /* Status 1 */
#define AK8963_REG_HXL              0x03
#define AK8963_REG_HXH              0x04
#define AK8963_REG_HYL              0x05
#define AK8963_REG_HYH              0x06
#define AK8963_REG_HZL              0x07
#define AK8963_REG_HZH              0x08
#define AK8963_REG_ST2              0x09    /* Status 2 */
#define AK8963_REG_CNTL1            0x0A    /* Control 1 */
#define AK8963_REG_CNTL2            0x0B    /* Control 2 */
#define AK8963_REG_ASTC             0x0C    /* Self-test */
#define AK8963_REG_TS1              0x0D    /* Test 1 */
#define AK8963_REG_TS2              0x0E    /* Test 2 */
#define AK8963_REG_I2CDIS           0x0F    /* I2C Disable */
#define AK8963_REG_ASAX             0x10    /* X-axis sensitivity adjustment value */
#define AK8963_REG_ASAY             0x11    /* Y-axis sensitivity adjustment value */
#define AK8963_REG_ASAZ             0x12    /* Z-axis sensitivity adjustment value */
#define AK8963_REG_RSV              0x13    /* Reserved */

#define MPU_DEVICE_ID               0x68
#define AK8963_DEVICE_ID            0x48

#define BIT_SLEEP                   0x40
#define BIT_H_RESET                 0x80
#define BITS_CLKSEL                 0x07
#define MPU_CLK_SEL_PLLGYROX        0x01
#define MPU_CLK_SEL_PLLGYROZ        0x03
#define MPU_EXT_SYNC_GYROX          0x02
#define BITS_FS_250DPS              0x00
#define BITS_FS_500DPS              0x08
#define BITS_FS_1000DPS             0x10
#define BITS_FS_2000DPS             0x18
#define BITS_FS_2G                  0x00
#define BITS_FS_4G                  0x08
#define BITS_FS_8G                  0x10
#define BITS_FS_16G                 0x18
#define BITS_FS_MASK                0x18
#define BITS_DLPF_CFG_256HZ         0x00
#define BITS_DLPF_CFG_188HZ         0x01
#define BITS_DLPF_CFG_98HZ          0x02
#define BITS_DLPF_CFG_42HZ          0x03
#define BITS_DLPF_CFG_20HZ          0x04
#define BITS_DLPF_CFG_10HZ          0x05
#define BITS_DLPF_CFG_5HZ           0x06
#define BITS_DLPF_CFG_2100HZ_NOLPF  0x07
#define BITS_DLPF_CFG_MASK          0x07
#define BIT_INT_ANYRD_2CLEAR        0x10
#define BIT_RAW_RDY_EN              0x01
#define BIT_I2C_IF_DIS              0x10
#define BIT_INT_STATUS_DATA         0x01
#define BIT_GYRO                    3
#define BIT_ACC                     2
#define BIT_TEMP                    1

#define ACC_GYRO_RAWDATA_LEN	    14

#define mpu6000_enable()            gpio_set_pin(GPIOC, GPIO_PIN_2)
#define mpu6000_disable()           gpio_reset_pin(GPIOC, GPIO_PIN_2)

static void mpu6000_write_reg(uint8_t reg, uint8_t data)
{
    mpu6000_enable();
    delay_ms(1);
    spi_transmit(0, &reg, 1, 1000);
    spi_transmit(0, &data, 1, 1000);
    mpu6000_disable();
    delay_ms(1);
}

static void mpu6000_read_reg(uint8_t reg, uint16_t len, void *data)
{
    mpu6000_enable();
    reg |= 0x80;
    spi_transmit(0, &reg, 1, 1000);
    spi_receive(0, data, len, 1000);
    mpu6000_disable();
}

static void mpu6000_read_h3vevtor(uint8_t reg, hvector3d_t *vec)
{
    mpu6000_read_reg(reg, 6, vec);
    vec->x = tole16(vec->x);
    vec->y = tole16(vec->y);
    vec->z = tole16(vec->z);
}

void mpu6000_read_gyro(hvector3d_t *gyro)
{
    mpu6000_read_h3vevtor(MPU_GYRO_XOUT_H, gyro);
}

void mpu6000_read_acc(hvector3d_t *acc)
{
    mpu6000_read_h3vevtor(MPU_ACCEL_XOUT_H, acc);
}

void mpu6000_init(void)
{
    unsigned char id;

    spi_set_speed(0, SPI_BAUDRATEPRESCALER_256);
    mpu6000_write_reg(MPU_PWR_MGMT1, BIT_H_RESET);
    delay_ms(50);
    mpu6000_write_reg(MPU_SIGNAL_PATH_RESET, BIT_GYRO | BIT_ACC | BIT_TEMP);
    delay_ms(50);
    mpu6000_write_reg(MPU_PWR_MGMT1, BIT_H_RESET);
    delay_ms(50);
    mpu6000_write_reg(MPU_SIGNAL_PATH_RESET, BIT_GYRO | BIT_ACC | BIT_TEMP);
    delay_ms(50);

    mpu6000_read_reg(MPU_WHO_AM_I, 1, &id);
    if (id != MPU_DEVICE_ID) {
        Error_Handler();
    }

    mpu6000_write_reg(MPU_PWR_MGMT1, MPU_CLK_SEL_PLLGYROX);
    delay_ms(15);
    mpu6000_write_reg(MPU_PWR_MGMT2, 0);
    delay_ms(15);
    mpu6000_write_reg(MPU_SMPLRT_DIV, 0);
    delay_ms(15);
    mpu6000_write_reg(MPU_GYRO_CONFIG, 0x03 << 3);
    delay_ms(15);
    mpu6000_write_reg(MPU_ACCEL_CONFIG, 0x02 << 3);
    delay_ms(15);
    mpu6000_write_reg(MPU_INT_PIN_CFG, 0x10);
    delay_ms(15);
    mpu6000_write_reg(MPU_CONFIG, BITS_DLPF_CFG_98HZ);
    delay_ms(15);
    spi_set_speed(0, SPI_BAUDRATEPRESCALER_128);
}
