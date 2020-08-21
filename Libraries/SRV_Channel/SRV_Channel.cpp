#include <AP_Math.h>
#include "SRV_Channel.h"

SRV_Channel::SRV_Channel(TIM_HandleTypeDef* pwm_tim,  // pwm timer
                         uint8_t            channel,  // pwm channel
                         uint16_t           pwm_max, 
                         uint16_t           pwm_min)
: _pwm_tim(pwm_tim)
, _channel(channel)
, _pwm_max(pwm_max)
, _pwm_min(pwm_min)
, _got_cmd(0)
{
  /* clear PWM */
  __HAL_TIM_SET_COMPARE(_pwm_tim,_channel, 0);
  HAL_TIM_PWM_Start(_pwm_tim, _channel);
  __HAL_TIM_SET_COMPARE(_pwm_tim,_channel, 1500);
}

void 
SRV_Channel::set_position(float value)
{
  if(!is_zero(value)){
    _got_cmd = 1;
  }
  if(_got_cmd == 1){
    _pwm = constrain_int16((int16_t)(((_pwm_max - _pwm_min) * (value + 1.0f)) / 2.0f) + _pwm_min, _pwm_min, _pwm_max);
    __HAL_TIM_SET_COMPARE(_pwm_tim,_channel, _pwm);
  }
}
