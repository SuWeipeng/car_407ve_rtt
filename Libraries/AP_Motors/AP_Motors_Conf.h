#ifndef __AP_MOTORS_CONF_H__
#define __AP_MOTORS_CONF_H__

#include <car_def.h>

#if MOTOR_TYPE == 0
#define MOTORS_PWM_MIN         50
#define ENCODER_CNT_MAX        65535
#define MOTORS_ENCODER_LINE    30.0f
#define MOTORS_MAX_RPM         160.0f
#define MOTORS_REDUCTION_RATIO 48.0f
#define ENCODER_DELTA_MAX      5000.0f
#elif MOTOR_TYPE == 1
#define MOTORS_PWM_MIN         50
#define ENCODER_CNT_MAX        65535
#define MOTORS_ENCODER_LINE    11.0f
#define MOTORS_MAX_RPM         275.0f
#define MOTORS_REDUCTION_RATIO 30.0f
#define ENCODER_DELTA_MAX      5000.0f
#elif MOTOR_TYPE == 2
#define MOTORS_PWM_MIN         50
#define ENCODER_CNT_MAX        65535
#define MOTORS_ENCODER_LINE    32.0f
#define MOTORS_MAX_RPM         235.0f
#define MOTORS_REDUCTION_RATIO 50.0f
#define ENCODER_DELTA_MAX      5000.0f
#elif MOTOR_TYPE == 3
#define MOTORS_PWM_MIN         50
#define ENCODER_CNT_MAX        65535
#define MOTORS_ENCODER_LINE    20.0f
#define MOTORS_MAX_RPM         120.0f
#define MOTORS_REDUCTION_RATIO 1.0f
#define ENCODER_DELTA_MAX      5000.0f
#endif

#endif /* __AP_MOTORS_CONF_H__ */
