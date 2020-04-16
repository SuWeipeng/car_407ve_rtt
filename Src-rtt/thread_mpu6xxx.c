/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-23     flybreak     the first version
 */

#include <rtthread.h>
#include "mpu6xxx.h"

/* Default configuration, please change according to the actual situation, support i2c and spi device name */
#define MPU6XXX_DEVICE_NAME  "i2c2"

rt_thread_t mpu_thread = RT_NULL;

struct mpu6xxx_3axes accel, gyro;
struct mpu6xxx_device *mpu6xxx_dev;

int mpu6xxx_initialize()
{
    /* Initialize mpu6xxx, The parameter is RT_NULL, means auto probing for i2c*/
    mpu6xxx_dev = mpu6xxx_init(MPU6XXX_DEVICE_NAME, RT_NULL);

    if (mpu6xxx_dev == RT_NULL)
    {
        rt_kprintf("mpu6xxx init failed\n");
        return -1;
    }
    rt_kprintf("mpu6xxx init succeed\n");
}

/* Test function */
int mpu6xxx_thread_entry(void* parameter)
{
    while(1)
    {
        if(mpu6xxx_dev == RT_NULL)
            return -1;

        mpu6xxx_get_accel(mpu6xxx_dev, &accel);
        mpu6xxx_get_gyro(mpu6xxx_dev, &gyro);

        rt_kprintf("accel.x = %3d, accel.y = %3d, accel.z = %3d \r\n", accel.x, accel.y, accel.z);
        rt_kprintf("gyro.x = %3d gyro.y = %3d, gyro.z = %3d\r\n", gyro.x, gyro.y, gyro.z);

        rt_thread_mdelay(100);
    }

    return 0;
}

