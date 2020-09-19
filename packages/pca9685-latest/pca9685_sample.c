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

static rt_thread_t tid1 = RT_NULL;

static void pca9685_sample_entry(void *parameter)
{
    rt_uint32_t count = 500;
    pca9685_device_t dev = RT_NULL;

    dev = pca9685_init(I2C_BUS, RT_NULL);

    if (dev == RT_NULL)
        goto _exit;

    pca9685_set_pwm(dev, 0, 0, 306);
    pca9685_set_pwm(dev, 1, 0, 500);
    pca9685_set_pwm(dev, 2, 0, 1000);

    while (count > 0)
    {
        count--;
        rt_thread_mdelay(10);
    }

_exit:    
    pca9685_deinit(dev);

}

int pca9685_sample(void)
{
    tid1 = rt_thread_create("pca9685_sample",
                            pca9685_sample_entry, RT_NULL,
                            512, 25, 10);

    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

		return 0;
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(pca9685_sample, a pca9685 sample);
#endif
