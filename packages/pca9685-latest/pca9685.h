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

#ifndef __PCA9685_H
#define __PCA9685_H

#include <rtthread.h>
#include <rtdevice.h>

#define PCA9685_ADDR_DEFAULT    0x40    /**< PCA9685 default address */
#define PWM_All_Call            0       /**< enable to let all pin outputs the same pwm time period */

#define PCA9685_SUBADR1         0x2     /**< i2c bus address 1 */
#define PCA9685_SUBADR2         0x3     /**< i2c bus address 2 */
#define PCA9685_SUBADR3         0x4     /**< i2c bus address 3 */

#define PCA9685_MODE1           0x0     /**< Mode Register 1 */
#define PCA9685_PRESCALE        0xFE    /**< Prescaler for PWM output frequency */

#define LED0_ON_L               0x6     /**< LED0 output and brightness control byte 0 */
#define LED0_ON_H               0x7     /**< LED0 output and brightness control byte 1 */
#define LED0_OFF_L              0x8     /**< LED0 output and brightness control byte 2 */
#define LED0_OFF_H              0x9     /**< LED0 output and brightness control byte 3 */

#define ALLLED_ON_L             0xFA    /**< load all the LEDn_ON registers, byte 0 */
#define ALLLED_ON_H             0xFB    /**< load all the LEDn_ON registers, byte 1 */
#define ALLLED_OFF_L            0xFC    /**< load all the LEDn_OFF registers, byte 0 */
#define ALLLED_OFF_H            0xFD    /**< load all the LEDn_OFF registers, byte 1 */

/* pca9685 device structure */
struct pca9685_device
{
    rt_device_t bus;
    rt_uint8_t i2c_addr;
};
typedef struct pca9685_device *pca9685_device_t;

/**
 * @brief set the frequency of pwm needed to output
 * 
 * @param dev the pointer of device structure
 * @param freq pwm frequency(24 < freq < 1526)
 */
void pca9685_set_pwm_freq(pca9685_device_t dev, float freq);

/**
 * @brief set the pwm pulse of one pin
 * 
 * @param dev the pointer of device structure
 * @param num the number of the pin needed to control
 * @param on pwm high level start time(0-4095)
 * @param off pwm high level stop time(0-4095)
 */
void pca9685_set_pwm(pca9685_device_t dev, rt_uint8_t num, rt_uint16_t on, rt_uint16_t off);

/**
 * @brief make pca9685 restart
 * 
 * @param dev the pointer of device structure
 */
void pca9685_restart(pca9685_device_t dev);

/**
 * This function initialize the pca9685 device.
 *
 * @param dev_name the name of i2c bus device
 * @param i2c_addr the i2c device address for i2c communication,RT_NULL use default address
 *
 * @return the pointer of device structure, RT_NULL reprensents  initialization failed.
 */
pca9685_device_t pca9685_init(const char *dev_name, rt_uint8_t i2c_addr);

/**
 * This function releases memory
 *
 * @param dev the pointer of device structure
 */
void pca9685_deinit(struct pca9685_device *dev);

#endif

