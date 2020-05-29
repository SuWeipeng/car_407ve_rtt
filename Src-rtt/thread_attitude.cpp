#if defined(USE_RTTHREAD)
#include <entry.h>
#include <AP_KF.h>

extern AP_KF *kalman_filter;

rt_thread_t attitude_thread = RT_NULL;

extern "C"
void attitude_thread_entry(void* parameter)
{
  while(1) {
    rt_thread_mdelay(30);
  }
}
#endif