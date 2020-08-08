#ifndef __DIFF_2WD_H__
#define __DIFF_2WD_H__

#if defined(STM32F407xx)
#include <stm32f4xx_hal.h>
#endif
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

class Diff_2wd : public AC_Base_Backend
{
public:
  Diff_2wd(AC_Base &instance);
  ~Diff_2wd();
  
  void vel2rpm(float& vel_x, float& vel_z);
  void pct2rpm(float& pct_x, float& pct_y, float& pct_z) override {}
  void pct2rpm(float& pct_x, float& pct_z) override;
//  void rpm2vel(const float &rpm1, const float &rpm2, const float &rpm4, 
//               float &vel_x, float &vel_y, float &vel_z);
  
  float get_vx(void) { return _vel_x; }
  float get_vz(void) { return _vel_z; }
  
#if defined(USE_RTTHREAD)
  void log_write_base();
#endif

private:
  AP_Motors _motor1_r;
  AP_Motors _motor2_l;
  AC_PID    _pid_1{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  AC_PID    _pid_2{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  
  float     _motor1_r_rpm, _motor2_l_rpm;
  float     _vel_x, _vel_y, _vel_z;
  
  void _run();
  
#if defined(USE_RTTHREAD) && defined(STM32F407xx)
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
#endif /*__DIFF_2WD_H__*/
