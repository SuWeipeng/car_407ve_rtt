#ifndef __AC_BASE_CONF_H__
#define __AC_BASE_CONF_H__

#include <car_def.h>

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
#define VEL_X_MAX_M_S       2.0f      // m/s
#define VEL_Y_MAX_M_S       2.0f      // m/s
#define VEL_Z_MAX_RAD_S     3.5f      // rad/s
#elif BASE_TYPE == 3
#define HALF_BASE_LENGTH_M  0.122f
#define HALF_BASE_WIDTH_M   0.0775f
#define WHEEL_DIAMETER_M    0.063f 
#define P                   0.33f
#define I                   3.3f
#define D                   0.0f
#define FF                  0.0f
#define IMAX                200.0f
#define FLTT                10.0f
#define FLTE                10.0f
#define FLTD                0.85f
#define DT                  0.02f
#define VEL_X_MAX_M_S       2.0f      // m/s
#define VEL_Y_MAX_M_S       2.0f      // m/s
#define VEL_Z_MAX_RAD_S     3.5f      // rad/s
#define VEL_XY_NOISE        0.015f    // m/s 
#define VEL_Z_NOISE         0.05f     // rad/s
#endif
  
#define WHEEL_RADIUS_M      (WHEEL_DIAMETER_M / 2.0f)
#define MECANUM_VCOM_DEBUG  0
#define PWM_RPM_TEST_ENABLE 0

#endif /* __AC_BASE_CONF_H__ */
