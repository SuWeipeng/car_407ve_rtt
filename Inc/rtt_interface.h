#ifndef __RTT_INTERFACE_H
#define __RTT_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <entry.h>
#include <mpu6xxx.h>
  
#define I2C2_SCL_PIN        GET_PIN(B, 10)
#define I2C2_SDA_PIN        GET_PIN(B, 11)
#define LED_PIN             GET_PIN(E, 0)
#define AP_BUFFER_MAX_SIZE  (1024 * 30)

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

extern struct      mpu6xxx_3axes accel, gyro;
extern uint8_t     mount_success;

extern rt_thread_t file_thread;
extern rt_thread_t led_thread;
extern rt_thread_t log_thread;
extern rt_thread_t mpu_thread;
extern rt_thread_t attitude_thread;

void file_log_entry (void* parameter);
void led_thread_entry(void* parameter);
void log_thread_entry(void* parameter);
void mpu6xxx_thread_entry(void* parameter);
void attitude_thread_entry(void* parameter);

int loop_start(void);

int mpu6xxx_initialize();

#ifdef __cplusplus
} // extern "C"
#endif

#endif
