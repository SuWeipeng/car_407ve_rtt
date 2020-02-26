#if defined(USE_RTTHREAD)
#include <entry.h>

rt_thread_t loop_thread = RT_NULL;

void loop (void* parameter);

int loop_start(void)
{
  rt_thread_mdelay(500);
  RTT_CREATE(loop,loop,RT_NULL,2048,5,20);
  return 0;
}

#endif
