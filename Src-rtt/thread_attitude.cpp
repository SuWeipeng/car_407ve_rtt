#if defined(USE_RTTHREAD)
#include <entry.h>
#include <rtt_interface.h>
#include <mpu6xxx.h>
#include <AP_KF.h>

extern struct mpu6xxx_3axes accel, gyro;
extern AP_KF *kalman_filter;

rt_thread_t attitude_thread = RT_NULL;

extern "C"
void attitude_thread_entry(void* parameter)
{
  while(1) {
    rt_sem_take(mpu_sem, RT_WAITING_FOREVER);
    rt_thread_mdelay(33);
  }
}
#endif