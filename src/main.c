#include <string.h>
#include <main.h>

extern int _write(int fd, char *ptr, int len);
void ano_dt_send_sensor(hvector3d_t *restrict gyro, hvector3d_t *restrict acc,
    hvector3d_t *restrict mag)
{
    unsigned char sum;
    unsigned char i, j;
    char data_to_send[254];

    i = 0;
    /* 帧头 */
    data_to_send[i++] = 0xAA;
    data_to_send[i++] = 0xAA;

    /* 功能字 */
    data_to_send[i++] = 0x02;
    data_to_send[i++] = 18;

    /* */
    data_to_send[i++] = (acc->x >> 8) & 0xFF;
    data_to_send[i++] = (acc->x) & 0xFF;
    data_to_send[i++] = (acc->y >> 8) & 0xFF;
    data_to_send[i++] = (acc->y) & 0xFF;
    data_to_send[i++] = (acc->z >> 8) & 0xFF;
    data_to_send[i++] = (acc->z) & 0xFF;
    data_to_send[i++] = (gyro->x >> 8) & 0xFF;
    data_to_send[i++] = (gyro->x) & 0xFF;
    data_to_send[i++] = (gyro->y >> 8) & 0xFF;
    data_to_send[i++] = (gyro->y) & 0xFF;
    data_to_send[i++] = (gyro->z >> 8) & 0xFF;
    data_to_send[i++] = (gyro->z) & 0xFF;
    data_to_send[i++] = (mag->x >> 8) & 0xFF;
    data_to_send[i++] = (mag->x) & 0xFF;
    data_to_send[i++] = (mag->y >> 8) & 0xFF;
    data_to_send[i++] = (mag->y) & 0xFF;
    data_to_send[i++] = (mag->z >> 8) & 0xFF;
    data_to_send[i++] = (mag->z) & 0xFF;
    for(sum = 0, j = 0; j < i; ++j) {
        sum += ((unsigned char *)data_to_send)[j];
    }
    data_to_send[i++] = sum;

    _write(0, data_to_send, i);
}

void ano_dt_send_status(float angle_rol, float angle_pit, float angle_yaw, int alt, unsigned char fly_model, unsigned char armed)
{
    int value;
    unsigned char sum;
    unsigned char i, j;
    char data_to_send[50];

    i = 0;
    data_to_send[i++] = 0xAA;
    data_to_send[i++] = 0xAA;
    data_to_send[i++] = 0x01;
    data_to_send[i++] = 0;
    value = (int)(angle_rol*100);
    data_to_send[i++] = (value >> 8) & 0xFF;
    data_to_send[i++] = value & 0xFF;
    value = (int)(angle_pit*100);
    data_to_send[i++] = (value >> 8) & 0xFF;
    data_to_send[i++] = value & 0xFF;
    value = (int)(angle_yaw*100);
    data_to_send[i++] = (value >> 8) & 0xFF;
    data_to_send[i++] = value & 0xFF;
    data_to_send[i++] = (alt >> 24) & 0xFF;
    data_to_send[i++] = (alt >> 16) & 0xFF;
    data_to_send[i++] = (alt >> 8) & 0xFF;
    data_to_send[i++] = alt & 0xFF;
    data_to_send[i++] = fly_model;
    data_to_send[i++] = armed;
    data_to_send[3] = i-4;
    for(sum = 0, j = 0; j < i; j++) {
        sum += ((unsigned char *)data_to_send)[j];
    }

    data_to_send[i++] = sum;
    _write(0, data_to_send, i);
}

void mpu6000_task(void *param)
{
    mpu6000_data_t data;
    fvector3d_t fv;
    euler_angle_t angle;
    QUATERNION_DEFAULT(q);
    char buf[64];
    int ret;

    while (1) {
        vPortEnterCritical();
        ret = mpu6000_receive_data(&data);
        vPortExitCritical();
        if (ret == 0) {
            continue;
        }

        fv.x = data.gyro.x;
        fv.y = data.gyro.y;
        fv.z = data.gyro.z;
        fvector3d_scale(&fv, &fv, degrees2radians(1.0f / 16.4f));
        quaternion_update_raw(&q, &fv, 0.001);
        quaternion_to_euler(&angle, &q);
        ret = snprintf(buf, sizeof(buf), "[%.3f, %.3f, %.3f]\r\n", angle.pitch, angle.roll, angle.yaw);
        _write(0, buf, ret);
    }
}

int main(void)
{
    xTaskCreate(mpu6000_task, "mpu6000 task", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}
