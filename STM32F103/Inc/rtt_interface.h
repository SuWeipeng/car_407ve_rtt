#ifndef __RTT_INTERFACE_H
#define __RTT_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <entry.h>

#define LED_PIN             GET_PIN(B, 7)

#if defined(__CC_ARM) || defined(__CLANG_ARM)
#pragma anon_unions
#endif
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

extern rt_sem_t    mode_sem;

extern rt_mq_t     mode_mq;

extern rt_thread_t led_thread;
extern rt_thread_t mode_thread;

void led_thread_entry(void* parameter);
void mode_thread_entry(void* parameter);

int loop_start(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
