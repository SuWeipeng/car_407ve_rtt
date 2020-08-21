#ifndef __SRV_CHANNEL_H__
#define __SRV_CHANNEL_H__

#include <stm32f4xx_hal.h>

#define SERVO_MAX_PWM (2500)
#define SERVO_MIN_PWM (500)

class SRV_Channel{
  public:
  SRV_Channel(TIM_HandleTypeDef* pwm_tim,  // pwm timer
              uint8_t            channel,  // pwm channel
              uint16_t           pwm_max,
              uint16_t           pwm_min);
              
  void set_position(float value);            // value from 0.0f to 1.0f
  
  private:
  TIM_HandleTypeDef* _pwm_tim;
  uint8_t            _channel;
  uint16_t           _pwm_max;
  uint16_t           _pwm_min;
  uint16_t           _pwm;
  uint8_t            _got_cmd;
};

#endif /* __SRV_CHANNEL_H__ */