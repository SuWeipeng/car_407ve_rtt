#ifndef __AP_MOTORS_H__
#define __AP_MOTORS_H__

#include <stm32f4xx_hal.h>
#include "AP_Motors_Conf.h"

#define MOTORS_VCOM_DEBUG      3

class AP_Motors_Backend;
class AC_PID;

class AP_Motors
{
  friend class AP_Motors_Backend;
  friend class AP_Motors_L298N_3Wire_ABEncoder;
public:  
  AP_Motors();
  
    // get singleton
  static AP_Motors *get_instance(void) {
    return _instance;
  }
  
  /* Do not allow copies */
  AP_Motors(const AP_Motors &other) = delete;
  AP_Motors &operator=(const AP_Motors&) = delete;
  
  /* L298N_3Wrie_ABEncoder */
  void     init(TIM_HandleTypeDef* enc_tim,  // encoder timer
                int8_t             enc_dir,  // encoder direction
                GPIO_TypeDef*      dir_port, // L298N GPIO port
                uint16_t           pin_1,    // L298N in1
                uint16_t           pin_2,    // L298N in2
                TIM_HandleTypeDef* pwm_tim,  // pwm timer
                uint8_t            channel,  // pwm channel
                uint16_t           pwm_max,
                AC_PID*            pid);
  
  void     set_rpm(float rpm);
  AC_PID*  get_pid() { return _pid; }
  int32_t  get_delta_tick();
  int32_t  get_tick();
  double   get_delta_min();
  int16_t  get_pwm();
  uint16_t get_delta_ms();
  float    get_rpm();
  float    get_rpm_target();
  float    get_rpm_encoder();

private:
  static AP_Motors*       _instance;
  AP_Motors_Backend*      _backend;
  AC_PID*                 _pid;
};
#endif /* __AP_MOTORS_H__ */
