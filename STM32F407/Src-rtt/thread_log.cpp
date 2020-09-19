#if defined(USE_RTTHREAD)
#include <entry.h>
#include "AC_Base.h"

extern AC_Base *base;
extern uint8_t mount_success;

rt_thread_t log_thread = RT_NULL;

extern "C"
void log_thread_entry(void* parameter)
{
  static uint16_t cnt = 1000;
  while(1) {
    if(mount_success == 0){
      cnt--;
      if(cnt == 0){
        return;
      }
    }
    base->log_write_base();
    rt_thread_delay(1);
  }
}
#endif
