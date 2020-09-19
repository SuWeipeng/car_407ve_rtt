/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-15     greedyhao    first version
 */

#include <rtthread.h>
#include "pca9685.h"

// #define DBG_ENABLE
#define DBG_SECTION_NAME     "pca9685"
#define DBG_LEVEL            DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

#define I2C_BUS    "i2c1"

rt_thread_t pca9685_thread = RT_NULL;

void pca9685_thread_entry(void *parameter)
{
    pca9685_device_t dev = RT_NULL;

    dev = pca9685_init(I2C_BUS, RT_NULL);

    if (dev == RT_NULL){
      pca9685_deinit(dev);
      return;
    }

    pca9685_set_pwm(dev, 0, 0, 306);
    pca9685_set_pwm(dev, 1, 0, 500);
    pca9685_set_pwm(dev, 2, 0, 1000);

    while (1)
    {
      rt_thread_mdelay(1);
    }
}
