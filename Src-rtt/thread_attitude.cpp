#if defined(USE_RTTHREAD)
#include <entry.h>
#include <rtt_interface.h>
#include <mpu6xxx.h>
#include <AP_KF.h>
#include <vector3.h>
#include <Logger.h>

extern struct mpu6xxx_3axes accel, gyro;
extern AP_KF *kalman_filter;

rt_thread_t attitude_thread = RT_NULL;

extern "C"
void attitude_thread_entry(void* parameter)
{
  uint32_t time_last = 0;
  Vector3f acc, acc_norm;
  float    dt;
  int16_t  temp;
  while(1) {
    rt_sem_take(mpu_sem, RT_WAITING_FOREVER);
    
    temp    = accel.x;
    accel.x = -accel.y;
    accel.y = -temp;
    
    temp    = gyro.x;
    gyro.x  = -gyro.y;
    gyro.y  = -temp;
    
    acc(accel.x, accel.y, accel.z);
    acc_norm = acc / acc.length();
    
    float roll_acc  = -asin(acc_norm.y);
    float pitch_acc = atan2f(acc_norm.x, acc_norm.z);
    
    Vector2f attitude(roll_acc, pitch_acc), gyroscope(gyro.x, gyro.y);
    gyroscope = gyroscope * M_PI / 18000;
    
    dt = (HAL_GetTick() - time_last) / 1000.0f;
    kalman_filter->set_dt(dt);
    _Vector4f att_flt = kalman_filter->run(attitude, gyroscope);
    
    Vector2f att_var  = kalman_filter->get_att_var();
    Vector2f gyro_var = kalman_filter->get_gyro_var();
    Write_Attitude(roll_acc, pitch_acc, gyroscope.x, gyroscope.y, att_flt[0], att_flt[2], att_flt[1], att_flt[3],att_var.x, att_var.y, gyro_var.x, gyro_var.y);
    
    time_last = HAL_GetTick();
    rt_thread_mdelay(33);
  }
}
#endif