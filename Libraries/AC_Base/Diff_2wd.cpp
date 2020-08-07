#include <stdio.h>
#include <vectorN.h>
#include "Diff_2wd.h"
#if defined(STM32F407xx)
#include "Logger.h"
#endif
#if (PWM_RPM_TEST_ENABLE == 1) || (MOTORS_VCOM_DEBUG == 2)
#include <stm32f4xx_hal.h>
#include "mavlink.h"

extern UART_HandleTypeDef huart1;
#endif

#if MOTORS_VCOM_DEBUG == 2 || MOTORS_VCOM_DEBUG == 3
extern rt_device_t vcom;
#endif

typedef VectorN<float,2> _Vector2f;

static float r1[3] = { 1,  HALF_BASE_WIDTH_M};
static float r2[3] = { 1, -HALF_BASE_WIDTH_M};

static _Vector2f _r1(r1),_r2(r2);

Diff_2wd::Diff_2wd(AC_Base &instance)
: AC_Base_Backend(instance)
, _motor1_r_rpm(0.0f)
, _motor2_l_rpm(0.0f)
, _vel_x(0)
, _vel_y(0)
, _vel_z(0)
#if defined(USE_RTTHREAD) && defined(STM32F407xx)
, _log_sem("log",0)
#endif
{
#if defined(STM32F407xx)
  _motor1_r.init(&htim3, 1, GPIOC, GPIO_PIN_1, GPIO_PIN_3, &htim5, TIM_CHANNEL_4, 99, &_pid_1);
  _motor2_l.init(&htim1, 1, GPIOE, GPIO_PIN_2, GPIO_PIN_4, &htim5, TIM_CHANNEL_1, 99, &_pid_2);
#endif
}

Diff_2wd::~Diff_2wd()
{}

void Diff_2wd::vel2rpm(float& vel_x, float& vel_z)
{
  double scale = 1;
  float  vel[2] = {vel_x, vel_z};
  _Vector2f _vel(vel);
  
  /* check rpm max  */
  while(1)
  {
    _motor1_r_rpm = (_r1 * _vel) / WHEEL_RADIUS_M;
    _motor1_r_rpm *= 9.55f; // rad/s -> rpm
    _motor2_l_rpm = (_r2 * _vel) / WHEEL_RADIUS_M;
    _motor2_l_rpm *= 9.55f; // rad/s -> rpm
    if(fabsf(_motor1_r_rpm) <= MOTORS_MAX_RPM 
    && fabsf(_motor2_l_rpm) <= MOTORS_MAX_RPM)
    {
      break;
    }
    scale -= 0.0333334;
    _vel  *= scale;
  }
  
  _run();
}

void Diff_2wd::pct2rpm(float& pct_x, float& pct_z)
{
  double scale = 1;
  float  vel[3] = {pct_x * VEL_X_MAX_M_S, pct_z * VEL_Z_MAX_RAD_S};
  _Vector2f _vel(vel);
  
  /* check rpm max  */
  while(1)
  {
    _motor1_r_rpm = (_r1 * _vel) / WHEEL_RADIUS_M;
    _motor1_r_rpm *= 9.55f; // rad/s -> rpm
    _motor2_l_rpm = (_r2 * _vel) / WHEEL_RADIUS_M;
    _motor2_l_rpm *= 9.55f; // rad/s -> rpm
    if(fabsf(_motor1_r_rpm) <= MOTORS_MAX_RPM 
    && fabsf(_motor2_l_rpm) <= MOTORS_MAX_RPM)
    {
      break;
    }
    scale -= 0.0333334;
    _vel  *= scale;
  }
  
  _run();
}

void Diff_2wd::_run()
{
  _motor1_r.set_rpm(_motor1_r_rpm);
  _motor2_l.set_rpm(_motor2_l_rpm);

//  rpm2vel(_motor1_fr.get_rpm(), _motor3_bl.get_rpm(), _motor4_br.get_rpm(),
//          _vel_x, _vel_y, _vel_z);
  
#if MOTORS_VCOM_DEBUG == 3 && defined(STM32F407xx)
  if(vcom != RT_NULL){
    char buf[100];
    sprintf(buf, "s: [vel_x: %.2f, vel_y: %.2f, vel_z: %.5f, rpm: %.2f, pwm: %d]\r\n", _vel_x, _vel_y, _vel_z, _motor1_fr.get_rpm(), _motor1_fr.get_pwm());
    rt_device_write(vcom, 0, buf, rt_strlen(buf));
  }
#endif
  
#if defined(USE_RTTHREAD) && defined(STM32F407xx)
  _log_sem.release();
#endif
#if PWM_RPM_TEST_ENABLE == 1
  _pwm_rpm_test();
#endif

#if MOTORS_VCOM_DEBUG == 2 && defined(STM32F407xx)
  _rpm_test();
  if(vcom != RT_NULL){
    char buf[100];
    sprintf(buf, "[rpm: %.1f]\r\n", _motor2_fl.get_rpm());
    rt_device_write(vcom, 0, buf, rt_strlen(buf));
  }
#endif
}

//void Diff_2wd::rpm2vel(const float &rpm1, const float &rpm3, const float &rpm4, 
//                          float &vel_x, float &vel_y, float &vel_z)
//{
//  vel_x = (rpm3 + rpm4) * 0.10472 * WHEEL_RADIUS_M / 2;
//  vel_y = (rpm1 - rpm4) * 0.10472 * WHEEL_RADIUS_M / 2;
//  vel_z = (rpm1 - rpm3) * 0.10472 * WHEEL_RADIUS_M / (2 * (HALF_BASE_LENGTH_M+HALF_BASE_WIDTH_M));
//  
//  if(fabsf(vel_x) < VEL_XY_NOISE) vel_x = 0.0f;
//  if(fabsf(vel_y) < VEL_XY_NOISE) vel_y = 0.0f;
//  if(fabsf(vel_z) < VEL_Z_NOISE) vel_z = 0.0f;
//}
  
#if defined(USE_RTTHREAD) && defined(STM32F407xx)
void Diff_2wd::log_write_base()
{
  _log_sem.wait(RT_WAITING_FOREVER);
  
  Write_PID(LOG_PIDW1_MSG, &_motor1_fr.get_pid()->get_pid_info());
  Write_PID(LOG_PIDW2_MSG, &_motor2_fl.get_pid()->get_pid_info());
  Write_PID(LOG_PIDW3_MSG, &_motor3_bl.get_pid()->get_pid_info());
  Write_PID(LOG_PIDW4_MSG, &_motor4_br.get_pid()->get_pid_info());
  
  Write_Encoder(LOG_ENC1_MSG, _motor1_fr.get_delta_tick(), _motor1_fr.get_tick(), _motor1_fr.get_delta_min(), _motor1_fr.get_delta_ms());
  Write_Encoder(LOG_ENC2_MSG, _motor2_fl.get_delta_tick(), _motor2_fl.get_tick(), _motor2_fl.get_delta_min(), _motor2_fl.get_delta_ms());
  Write_Encoder(LOG_ENC3_MSG, _motor3_bl.get_delta_tick(), _motor3_bl.get_tick(), _motor3_bl.get_delta_min(), _motor3_bl.get_delta_ms());
  Write_Encoder(LOG_ENC4_MSG, _motor4_br.get_delta_tick(), _motor4_br.get_tick(), _motor4_br.get_delta_min(), _motor4_br.get_delta_ms());
  
  Write_PWM(_motor1_fr.get_pwm(), _motor2_fl.get_pwm(), _motor3_bl.get_pwm(), _motor4_br.get_pwm());
}
#endif

#if PWM_RPM_TEST_ENABLE == 1
void Diff_2wd::_pwm_rpm_test()
{
  mavlink_message_t msg;
  int len = 0;
  uint8_t myTxData[32];
  
  mavlink_msg_pwm_rpm_pack(0, 0, &msg, _motor1_fr.get_pwm(), _motor1_fr.get_rpm_encoder());
  len = mavlink_msg_to_send_buffer( myTxData, &msg );
  HAL_UART_Transmit(&huart1,myTxData,len,10);
}
#endif

#if MOTORS_VCOM_DEBUG == 2
void Diff_2wd::_rpm_test()
{
  mavlink_message_t msg;
  int len = 0;
  uint8_t myTxData[32];

  mavlink_msg_rpm_pack(0, 0, &msg,  HAL_GetTick(), _motor2_fl.get_rpm_target(), _motor2_fl.get_rpm());
  len = mavlink_msg_to_send_buffer( myTxData, &msg );
  HAL_UART_Transmit(&huart1,myTxData,len,10);
}
#endif
