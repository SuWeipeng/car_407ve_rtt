#ifndef __RTT_INTERFACE_H
#define __RTT_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <entry.h>

#define LED_PIN             GET_PIN(E, 0)

extern rt_thread_t led_thread;

void led_thread_entry(void* parameter);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
