#ifndef __RTT_INTERFACE_H
#define __RTT_INTERFACE_H

#include <entry.h>

#define LED_PIN    GET_PIN(B, 12)
typedef union{
  struct{
    uint8_t key_value: 3;
    uint8_t w_number : 2;
    uint8_t mode     : 2;
    uint8_t com      : 1;
  };
  uint8_t value;
}ap_t;

typedef struct vel_target {
  float vel_x; // m/s
  float vel_y; // m/s
  float rad_z; // rad/s
} vel_target;

extern rt_thread_t led_thread;
extern rt_thread_t log_thread;

void led_thread_entry(void* parameter);
void log_thread_entry(void* parameter);

#endif
