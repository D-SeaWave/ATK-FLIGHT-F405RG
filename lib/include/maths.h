#ifndef __LIB_MATHS_H__
#define __LIB_MATHS_H__

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#define float   float
#define M_PIf   acosf(-1.0f)
#define SQRTF   sqrtf
#define FABSF   fabsf
#define ASINF   asinf
#define ATAN2F  atan2f

#define QUATERNION_DEFAULT_INITIALIZER      {1.0, 0.0, 0.0, 0.0}
#define QUATERNION_DEFAULT(q)               \
    quaternion_t q = QUATERNION_DEFAULT_INITIALIZER

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} hvector3d_t;

typedef struct {
    float x;
    float y;
    float z;
} fvector3d_t;

typedef struct {
    float pitch;    /* 俯仰角 */
    float roll;     /* 横滚角 */
    float yaw;      /* 偏航角 */
} euler_angle_t;

typedef float quaternion_t[4];

static inline float degrees2radians(const float degrees)
{
    return degrees * (M_PIf / 180.0f);
}

static inline float radians2degrees(const float rad)
{
    return rad * (180.0f / M_PIf);
}

static inline int16_t tole16(int16_t raw_value)
{
    return (raw_value << 8) | (raw_value >> 8);
}

extern float fvector3d_square(const fvector3d_t *v);

extern void fvector3d_add(fvector3d_t *res, const fvector3d_t *v, const fvector3d_t *value);

extern void fvector3d_scale(fvector3d_t *res, const fvector3d_t *v, const float t);

extern void fvector3d_vscale(fvector3d_t *res, const fvector3d_t *v, const fvector3d_t *t);

extern void fvector3d_normalize(fvector3d_t *res, const fvector3d_t *v);

extern void hvector3d_add(hvector3d_t *res, const hvector3d_t *v, const hvector3d_t *value);

extern void hvector3d_scale(hvector3d_t *res, const hvector3d_t *v, const short t);

extern void hvector3d_vscale(hvector3d_t *res, const hvector3d_t *v, const hvector3d_t *t);

/**
 * quaternion_normalize 四元数归一化
 *
 * @q 四元数
 */
extern void quaternion_normalize(quaternion_t *q);

/**
 * quaternion_update 四元数更新，使用四阶毕卡解法
 * 
 * @q 四元数
 * @delta 3轴角增量
 */
extern void quaternion_update(quaternion_t *restrict q, const fvector3d_t *restrict delta);

/**
 * quaternion_update 四元数更新，使用四阶毕卡解法
 * 
 * @q 四元数
 * @w 3轴角速度
 * @dt 采样间隔时间
 */
extern void quaternion_update_raw(quaternion_t *restrict q, const fvector3d_t *restrict w,
    const float dt);

/**
 * quaternion_to_euler 四元数求欧拉角
 *
 * @angle 欧拉角，弧度值
 * @q 四元数
 */
extern void quaternion_to_euler(euler_angle_t *restrict angle, const quaternion_t *restrict q);

/**
 * @brief bits_count 计算出一个整数中1的位数
 */
extern unsigned char bits_count(unsigned int i);

/**
 * @brief gcd 求解最大公约数
 */
extern int gcd(const int a, const int b);

/**
 * @brief gaussian_elimination 高斯消元法求解
 * @param matrix 矩阵, 增广矩阵[a * x | b], 其中 [a * x]是个rows*rows行的方阵, [b]是个长度位rows的列向量
 * @param res 解的存放位置, 是个长度为rows的数组
 * @param rows 增广矩阵的行数
 * @return 方程有解返回，如果没有解，返回-1
 */
extern int gaussian_elimination(float *restrict matrix, float *restrict res, const unsigned int rows);

#endif /* __LIB_MATHS_H__ */
