#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maths.h"

float fvector3d_square(const fvector3d_t *restrict v)
{
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

float fvector3d_size(const fvector3d_t *v)
{
    return sqrtf(fvector3d_square(v));
}

void fvector3d_add(fvector3d_t *res, const fvector3d_t *v, const fvector3d_t *value)
{
    res->x = v->x + value->x;
    res->y = v->y + value->y;
    res->z = v->z + value->z;
}

void fvector3d_scale(fvector3d_t *res, const fvector3d_t *v, const float t)
{
    res->x = v->x * t;
    res->y = v->y * t;
    res->z = v->z * t;
}

void fvector3d_vscale(fvector3d_t *res, const fvector3d_t *v, const fvector3d_t *t)
{
    res->x = v->x * t->x;
    res->y = v->y * t->y;
    res->z = v->z * t->z;
}

void fvector3d_normalize(fvector3d_t *res, const fvector3d_t *v)
{
    float size;

    size = fvector3d_square(v);
    if (size == 0.0f) {
        res->x = 0.0f;
        res->y = 0.0f;
        res->z = 0.0f;
        return;
    }

    size = sqrtf(size);
    res->x = v->x / size;
    res->y = v->y / size;
    res->z = v->z / size;
}

short hvector3d_square(const hvector3d_t *v)
{
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

void hvector3d_add(hvector3d_t *res, const hvector3d_t *v, const hvector3d_t *value)
{
    res->x = v->x + value->x;
    res->y = v->y + value->y;
    res->z = v->z + value->z;
}

void hvector3d_scale(hvector3d_t *res, const hvector3d_t *v, const short t)
{
    res->x = v->x * t;
    res->y = v->y * t;
    res->z = v->z * t;
}

void hvector3d_scale3x(hvector3d_t *res, const hvector3d_t *v, const hvector3d_t *t)
{
    res->x = v->x * t->x;
    res->y = v->y * t->y;
    res->z = v->z * t->z;
}

unsigned char bits_count(unsigned int i)
{
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);

    return (i & 0x3f);
}

int gcd(const int a, const int b)
{
    return (a % b == 0) ? b : gcd(b, a % b);
}

int gaussian_elimination(float *restrict matrix, float *restrict res, const unsigned int rows)
{
    int ret;
    unsigned int j, i;
    unsigned int max_main_element_row, row_offset;
    unsigned int next_row, next_offset, current_offset;
    float current_main_element, temp, sum;
    const unsigned int columns = rows + 1;

    if (matrix == NULL || res == NULL || rows == 0) {
        return -1;
    }

    ret = 0;
    /* 化成三角形 */
    for (j = 0; j < rows; ++j) {
        max_main_element_row = j;
        current_offset = j * columns + j;
        row_offset = current_offset;
        current_main_element = FABSF(matrix[current_offset]);

        /* 1. 将列主元最大的行移到剩余行中的第一行 */
        /* 1.1 找出主元最大的一行 */
        for (next_offset = current_offset + columns, next_row = j + 1; next_row < rows;
                ++next_row, next_offset += columns) {
            if (FABSF(matrix[next_offset]) > current_main_element) {
                max_main_element_row = next_row;
                row_offset = next_offset;
            }
        }
        /* 1.2 交换两行的顺序 */
        if (max_main_element_row != j) {
            for (i = 0; i + j < columns; ++i) {
                /* 前面都是0, 所以不用再交换 */
                temp = matrix[current_offset + i];
                matrix[current_offset + i] = matrix[row_offset + i];
                matrix[row_offset + i] = temp;
            }
        }

        /* 2. 消主元 */
        for (next_offset = current_offset + columns, next_row = j + 1; next_row < rows;
                ++next_row, next_offset += columns) {
            if (matrix[next_offset] == 0.0) {
                continue;
            }

            temp = matrix[current_offset] / matrix[next_offset];
            matrix[next_offset] = 0.0;
            for (i = 1; i + j < columns; ++i) {
                matrix[next_offset + i] = matrix[next_offset + i] * temp
                    - matrix[current_offset + i];
            }
        }

    }

    /* 回代求解 */
    row_offset = rows * columns;
    for (j = rows; j-- > 0; row_offset -= columns) {
        if (matrix[row_offset + j] == 0.0) {
            /* 无唯一解 */
            ret = -1;
            break;
        }

        for (sum = 0.0, i = columns - 2; i > j; --i) {
            sum += res[i] * matrix[row_offset + i];
        }
        res[j] = (matrix[row_offset + rows] - sum) / matrix[row_offset + j];
    }

    return ret;
}
