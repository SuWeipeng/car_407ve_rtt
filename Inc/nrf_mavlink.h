#ifndef __NRF_MAVLINK_H
#define __NRF_MAVLINK_H

#include <stm32f4xx_hal.h>
#include "mavlink.h"

typedef union{
  struct{
    uint8_t key_value: 3;
    uint8_t w_number : 2;
    uint8_t mode     : 2;
    uint8_t com      : 1;
  };
  uint8_t value;
}ap_t;

void update_mavlink(void);

#endif
