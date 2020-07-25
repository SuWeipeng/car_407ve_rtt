#ifndef __AP_MOTORS_BACKEND_H__
#define __AP_MOTORS_BACKEND_H__

#include "AP_Motors.h"

class AP_Motors_Backend
{
public:
  AP_Motors_Backend(AP_Motors &instance);
  
  virtual void     set_rpm(float rpm) = 0;
  virtual AC_PID*  get_pid()        { return nullptr; }
  virtual int32_t  get_delta_tick() { return 0; }
  virtual int32_t  get_tick()       { return 0; }
  virtual double   get_delta_min()  { return 0.0; }
  virtual int16_t  get_pwm()        { return 0; }
  virtual uint16_t get_delta_ms()   { return 0; }
  virtual float    get_rpm()        { return 0.0f; }
  virtual float    get_rpm_target() { return 0.0f; }
  virtual float    get_rpm_encoder(){ return 0.0f; }
  
protected:
  AP_Motors &_frontend;
};
#endif /* __AP_MOTORS_BACKEND_H__ */
