#ifndef __AP_MOTORS_L298N_3WIRE_SINGLEENCODER_H__
#define __AP_MOTORS_L298N_3WIRE_SINGLEENCODER_H__

#include "AP_Motors_Backend.h"

#define MOTORS_L298N_3WIRE_ABENCODER_VCOM_DEBUG      0

class AP_Motors_L298N_3Wire_SingleEncoder : public AP_Motors_Backend
{
public:
  AP_Motors_L298N_3Wire_SingleEncoder(AP_Motors          &instance,
                                  TIM_HandleTypeDef* enc_tim,  // encoder timer
                                  int8_t             enc_dir,  // encoder direction
                                  GPIO_TypeDef*      dir_port, // L298N GPIO port
                                  uint16_t           pin_1,    // L298N in1
                                  uint16_t           pin_2,    // L298N in2
                                  TIM_HandleTypeDef* pwm_tim,  // pwm timer
                                  uint8_t            channel,  // pwm channel
                                  uint16_t           pwm_max,
                                  AC_PID*            pid);
  
  void     set_rpm(float rpm) override;
  AC_PID*  get_pid()          override        { return _pid; }
  int32_t  get_delta_tick()   override        { return _delta_tick; }
  int32_t  get_tick()         override        { return _tick; }
  double   get_delta_min()    override        { return _delta_min; }
  int16_t  get_pwm()          override        { return _pwm; }
  uint16_t get_delta_ms()     override        { return _delta_ms; }
  float    get_rpm()          override        { return _rpm; }
  float    get_rpm_target()   override        { return _rpm_target; }
  float    get_rpm_encoder()  override        { return _rpm_encoder; }

private:
  /* encoder */
  TIM_HandleTypeDef* _enc_tim;
  int8_t             _enc_dir;
  int32_t            _tick;
  int32_t            _tick_last;
  uint32_t           _last_millisecond;
  float              _rpm;
  float              _rpm_target;
  float              _rpm_last;
  float              _rpm_encoder;
  int32_t            _delta_tick;
  double             _delta_min;
  uint16_t           _delta_ms;
  
  /* L298N */
  TIM_HandleTypeDef* _pwm_tim;
  uint8_t            _channel;
  uint16_t           _pwm_max;
  GPIO_TypeDef*      _dir_port;
  uint16_t           _pin_1;
  uint16_t           _pin_2;
  int16_t            _pwm;
  
  /* pid control */
  AC_PID*            _pid;
  
  void     _spin(int16_t pwm);
  float    _read_rpm();
  int32_t  _get_delta_tick();
};
#endif /* __AP_MOTORS_L298N_3WIRE_SINGLEENCODER_H__ */
