#ifndef __MECANUM_4WD_H__
#define __MECANUM_4WD_H__

#include <stm32f4xx_hal.h>
#include <AP_Motors.h>
#include <AC_PID.h>

#if defined(USE_RTTHREAD)
#include "Semaphore.h"
using namespace rtthread;
#endif

#define BASE_TYPE           0 // 0-Small, 1-Middle, 2-Test
#if BASE_TYPE == 0
#define HALF_BASE_LENGTH_M  0.065f
#define HALF_BASE_WIDTH_M   0.080f
#define WHEEL_DIAMETER_M    0.097f 
#define P                   0.23f
#define I                   3.3f
#define D                   0.0f
#define FF                  0.0f
#define IMAX                200.0f
#define FLTT                10.0f
#define FLTE                10.0f
#define FLTD                0.85f
#define DT                  0.02f
#define VEL_X_MAX_M_S       0.75f     // m/s
#define VEL_Y_MAX_M_S       0.75f     // m/s
#define VEL_Z_MAX_RAD_S     5.3f      // rad/s
#define VEL_XY_NOISE        0.025f    // m/s 
#define VEL_Z_NOISE         0.075f    // rad/s
#elif BASE_TYPE == 1
#define HALF_BASE_LENGTH_M  0.122f
#define HALF_BASE_WIDTH_M   0.120f
#define WHEEL_DIAMETER_M    0.060f 
#define P                   0.5f
#define I                   5.0f
#define D                   0.0f
#define FF                  0.0f
#define IMAX                200.0f
#define FLTT                0.0f
#define FLTE                0.0f
#define FLTD                0.85f
#define DT                  0.02f
#define VEL_X_MAX_M_S       0.85f     // m/s
#define VEL_Y_MAX_M_S       0.85f     // m/s
#define VEL_Z_MAX_RAD_S     3.5f      // rad/s
#define VEL_XY_NOISE        0.015f    // m/s 
#define VEL_Z_NOISE         0.05f     // rad/s
#elif BASE_TYPE == 2
#define HALF_BASE_LENGTH_M  0.122f
#define HALF_BASE_WIDTH_M   0.120f
#define WHEEL_DIAMETER_M    0.096f 
#define P                   0.3f
#define I                   5.0f
#define D                   0.0f
#define FF                  0.0f
#define IMAX                200.0f
#define FLTT                0.0f
#define FLTE                0.0f
#define FLTD                0.85f
#define DT                  0.02f
#define VEL_X_MAX_M_S       2.0f      // m/min
#define VEL_Y_MAX_M_S       2.0f      // m/min
#define VEL_Z_MAX_RAD_S     3.5f       // RPM
#endif
  
#define WHEEL_RADIUS_M      (WHEEL_DIAMETER_M / 2.0f)
#define MECANUM_VCOM_DEBUG  0
#define PWM_RPM_TEST_ENABLE 0

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim8;

class Mecanum_4wd
{
public:
  Mecanum_4wd();
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
  AP_Motors _motor1_fr{&htim3, 1, GPIOC, GPIO_PIN_1, GPIO_PIN_3, &htim5, TIM_CHANNEL_4, 99, &_pid_1};
  AP_Motors _motor2_fl{&htim1, 1, GPIOE, GPIO_PIN_2, GPIO_PIN_4, &htim5, TIM_CHANNEL_1, 99, &_pid_2};
  AP_Motors _motor3_bl{&htim4, 1, GPIOE, GPIO_PIN_3, GPIO_PIN_5, &htim5, TIM_CHANNEL_2, 99, &_pid_3};
  AP_Motors _motor4_br{&htim8, 1, GPIOC, GPIO_PIN_0, GPIO_PIN_2, &htim5, TIM_CHANNEL_3, 99, &_pid_4};
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
