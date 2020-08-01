#ifndef __MECANUM_4WD_H__
#define __MECANUM_4WD_H__

#include <stm32f4xx_hal.h>
#include <AP_Motors.h>
#include <AC_PID.h>
#include "AC_Base_Backend.h"

#if defined(USE_RTTHREAD)
#include "Semaphore.h"
using namespace rtthread;
#endif

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim8;

class Mecanum_4wd : public AC_Base_Backend
{
public:
  Mecanum_4wd(AC_Base &instance);
  ~Mecanum_4wd();
  
  void vel2rpm(float& vel_x, float& vel_y, float& vel_z);
  void pct2rpm(float& pct_x, float& pct_y, float& pct_z);
  void rpm2vel(const float &rpm1, const float &rpm2, const float &rpm4, 
               float &vel_x, float &vel_y, float &vel_z);
  
  float get_vx(void) { return _vel_x; }
  float get_vy(void) { return _vel_y; }
  float get_vz(void) { return _vel_z; }
  
#if defined(USE_RTTHREAD)
  void log_write_base();
#endif

private:
  AP_Motors _motor1_fr;
  AP_Motors _motor2_fl;
  AP_Motors _motor3_bl;
  AP_Motors _motor4_br;
  AC_PID    _pid_1{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  AC_PID    _pid_2{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  AC_PID    _pid_3{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  AC_PID    _pid_4{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  
  float     _motor1_fr_rpm, _motor2_fl_rpm, _motor3_bl_rpm, _motor4_br_rpm;
  float     _vel_x, _vel_y, _vel_z;
  
  void _run();
  
#if defined(USE_RTTHREAD)
  Semaphore _log_sem;
#endif
 
#if PWM_RPM_TEST_ENABLE == 1
private:
  void      _pwm_rpm_test();
#endif

#if MOTORS_VCOM_DEBUG == 2
  void      _rpm_test();
#endif
};
#endif /*__MECANUM_4WD_H__*/
