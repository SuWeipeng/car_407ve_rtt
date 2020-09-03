#if defined(USE_RTTHREAD)
#include <entry.h>
#include <rtt_interface.h>
#include "SRV_Channel.h"

extern SRV_Channel *servo_bottom;
extern SRV_Channel *servo_top;
extern vel_target  vel;

rt_thread_t srv_thread = RT_NULL;

extern "C"
void srv_thread_entry(void* parameter)
{
  while(1) {
    servo_top->set_position(vel.ext_1 > -0.235f ? vel.ext_1 : -0.235f);
    servo_bottom->set_position(vel.ext_2);
    if(vel.ext_3 == 1){
      rt_pin_write(SHOOT_PIN, PIN_HIGH);
    }else{
      rt_pin_write(SHOOT_PIN, PIN_LOW);
    }
    rt_thread_delay(1);
  }
}
#endif
