#include <AP_Motors_L298N_3Wire_SingleEncoder.h>
#include <AP_Math.h>
#include <AC_PID.h>
#include <stdio.h>
#include <string.h>
#include <entry.h>

//#if MOTORS_L298N_3WIRE_ABENCODER_VCOM_DEBUG != 0
//extern rt_device_t vcom;
//#endif

AP_Motors_L298N_3Wire_SingleEncoder::AP_Motors_L298N_3Wire_SingleEncoder(AP_Motors          &instance,
                                                                 TIM_HandleTypeDef* enc_tim,  // encoder timer
                                                                 int8_t             enc_dir,  // encoder direction
                                                                 GPIO_TypeDef*      dir_port, // L298N GPIO port
                                                                 uint16_t           pin_1,    // L298N in1
                                                                 uint16_t           pin_2,    // L298N in2
                                                                 TIM_HandleTypeDef* pwm_tim,  // pwm timer
                                                                 uint8_t            channel,  // pwm channel
                                                                 uint16_t           pwm_max,
                                                                 AC_PID*            pid)
: AP_Motors_Backend(instance)
, _enc_tim(enc_tim)
, _enc_dir(enc_dir)
, _target_dir(0)
, _last_target_dir(0)
, _delta_tick_last(0)
, _tick(0)
, _tick_last(0)
, _last_millisecond(0)
, _rpm(0.0f)
, _rpm_target(0.0f)
, _rpm_last(0.0f)
, _rpm_encoder(0.0f)
, _delta_tick(0)
, _delta_min(0.0)
, _delta_ms(0)
, _pwm_tim(pwm_tim)
, _channel(channel)
, _pwm_max(pwm_max)
, _dir_port(dir_port)
, _pin_1(pin_1)
, _pin_2(pin_2)
, _pwm(0)
, _pid(pid)
{
  /* clear PWM */
  __HAL_TIM_SET_COMPARE(_pwm_tim,_channel, 0);
  HAL_TIM_PWM_Start(_pwm_tim, _channel);
  /* L298N brake */
  HAL_GPIO_WritePin(_dir_port, _pin_1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(_dir_port, _pin_2, GPIO_PIN_RESET);
  
  /* encoder */
  HAL_TIM_Base_Start(_enc_tim);
}

void AP_Motors_L298N_3Wire_SingleEncoder::set_rpm(float rpm)
{
  _rpm_target = rpm;

  if((_rpm_last>0 && _rpm_target<0) || (_rpm_last<0 && _rpm_target>0) || is_zero(_rpm_target)){
    _pid->reset_I();
    _rpm_last = _rpm_target;
  }

  _rpm_encoder = _read_rpm();
  _rpm = _rpm_encoder / MOTORS_REDUCTION_RATIO;
  _pwm = constrain_int16((int16_t)(_pid->update_all(_rpm_target, _rpm, false)+0.5f)+(int16_t)(_pid->get_ff()+0.5f), -_pwm_max, _pwm_max);
  
  /* The motor does not rotate when pwm lower than MOTORS_PWM_MIN*/
  if(abs(_pwm) < MOTORS_PWM_MIN) _pwm = 0;
  /* L298N deadzone */
  if((_rpm > 0 && _pwm < 0) || (_rpm < 0 && _pwm > 0)) _pwm = 0;
  
  /* spin */
  _spin(_pwm);
  
#if MOTORS_L298N_3WIRE_ABENCODER_VCOM_DEBUG == 1
  char buf[100];
  sprintf(buf, "[p:%.2f | i:%.2f | d:%.2f | pwm:%d | trpm:%.2f | rpm: %.2f] \r\n", _pid->get_p(), _pid->get_i(), _pid->get_d(), _pwm, rpm, _rpm);
  rt_kputs(buf);
#endif
}

void AP_Motors_L298N_3Wire_SingleEncoder::_spin(int16_t pwm)
{
  if(pwm > 0)
  {
    HAL_GPIO_WritePin(_dir_port, _pin_2, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(_dir_port, _pin_1, GPIO_PIN_SET);
  }
  if(pwm < 0) 
  {
    HAL_GPIO_WritePin(_dir_port, _pin_1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(_dir_port, _pin_2, GPIO_PIN_SET);
  }
  __HAL_TIM_SET_COMPARE(_pwm_tim,_channel, abs(pwm));
}

float AP_Motors_L298N_3Wire_SingleEncoder::_read_rpm()
{
  uint32_t cur_millisecond;
  float    delta_t_sec;
  double   rpm_cur;
  
  _delta_tick     = _get_delta_tick();
  cur_millisecond = HAL_GetTick();
  _delta_ms       = cur_millisecond - _last_millisecond;
  delta_t_sec     = _delta_ms / 1000.0f;
  _delta_min      = _delta_ms / 60000.0;

  rpm_cur = (_delta_tick / MOTORS_ENCODER_LINE) / _delta_min;
  
  _pid->set_dt(delta_t_sec);
                   
  _last_millisecond = cur_millisecond;
  
  return (float)rpm_cur;
}

int32_t AP_Motors_L298N_3Wire_SingleEncoder::_get_delta_tick()
{
  int32_t delta_tick;
 
  _tick = __HAL_TIM_GET_COUNTER(_enc_tim);

  if(abs(_tick - _tick_last) > ENCODER_DELTA_MAX ) /* overflow */
  {
    if(_tick > _tick_last)
    {
      delta_tick = -ENCODER_CNT_MAX - _tick_last + _tick;
    }else{
      delta_tick = ENCODER_CNT_MAX - _tick_last + _tick;
    }
  }else{
    delta_tick = _tick - _tick_last;
  }
  _tick_last = _tick;
  
  if(_target_dir != 0){
    if(_target_dir != _last_target_dir){
      if( delta_tick - _delta_tick_last > 0){
        _enc_dir = (_target_dir > 0) ? 1 : -1;
        _last_target_dir = _target_dir;
      }
    }
  }else{
    _last_target_dir = _target_dir;
  }
  
  delta_tick *= _enc_dir;
 
#if MOTORS_L298N_3WIRE_ABENCODER_VCOM_DEBUG == 1
  char buf[100];
  sprintf(buf, "[%4d|%4d]\r\n", delta_tick, _tick);
  rt_kputs(buf);
#endif
  
  return delta_tick;
}
