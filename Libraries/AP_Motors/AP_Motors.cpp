#include "AP_Motors.h"
#include "AP_Motors_L298N_3Wire_SingleEncoder.h"

AP_Motors *AP_Motors::_instance;

AP_Motors::AP_Motors()
: _backend(nullptr)
, _pid(nullptr)
{
  _instance = this;
}

void 
AP_Motors::init(TIM_HandleTypeDef* enc_tim,  // encoder timer
                int8_t             enc_dir,  // encoder direction
                GPIO_TypeDef*      dir_port, // L298N GPIO port
                uint16_t           pin_1,    // L298N in1
                uint16_t           pin_2,    // L298N in2
                TIM_HandleTypeDef* pwm_tim,  // pwm timer
                uint8_t            channel,  // pwm channel
                uint16_t           pwm_max,
                AC_PID*            pid)
{
  _backend = new AP_Motors_L298N_3Wire_SingleEncoder(*this,
                                                 enc_tim,
                                                 enc_dir,
                                                 dir_port,
                                                 pin_1,
                                                 pin_2,
                                                 pwm_tim,
                                                 channel,
                                                 pwm_max,
                                                 pid);
}

void     
AP_Motors::set_rpm(float rpm)
{
  if(_backend != nullptr){
    _backend->set_rpm(rpm);
  }
}

int32_t  
AP_Motors::get_delta_tick()
{
  if(_backend != nullptr){
    return _backend->get_delta_tick();
  }
  return 0;
}

int32_t  
AP_Motors::get_tick()
{
  if(_backend != nullptr){
    return _backend->get_tick();
  }
  return 0;
}

double   
AP_Motors::get_delta_min()
{
  if(_backend != nullptr){
    return _backend->get_delta_min();
  }
  return 0.0;
}

int16_t  
AP_Motors::get_pwm()
{
  if(_backend != nullptr){
    return _backend->get_pwm();
  }
  return 0;
}

uint16_t 
AP_Motors::get_delta_ms()
{
  if(_backend != nullptr){
    return _backend->get_delta_ms();
  }
  return 0;
}

float    
AP_Motors::get_rpm()
{
  if(_backend != nullptr){
    return _backend->get_rpm();
  }
  return 0.0f;
}

float    
AP_Motors::get_rpm_target()
{
  if(_backend != nullptr){
    return _backend->get_rpm_target();
  }
  return 0.0f;
}

float    
AP_Motors::get_rpm_encoder()
{
  if(_backend != nullptr){
    return _backend->get_rpm_encoder();
  }
  return 0.0f;
}
  
void    
AP_Motors::set_enc_dir(int dir)
{
  if(_backend != nullptr){
    _backend->set_enc_dir(dir);
  }
}
