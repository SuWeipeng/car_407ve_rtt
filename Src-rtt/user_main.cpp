#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdlib.h>
#include "rtt_interface.h"
#include "AC_Base.h"
#include "Logger.h"
#include "AP_Buffer.h"
#include "AP_RangeFinder.h"

using namespace rtthread;

extern vel_target vel;
extern rt_device_t vcom;

Mecanum_4wd *base;
AP_Buffer *buffer;
RangeFinder *range_finder;

extern "C" {
void setup(void)
{
  base = new Mecanum_4wd();
  buffer = new AP_Buffer();
  buffer->init(AP_Buffer::RING);
  range_finder =  new RangeFinder();
  range_finder->init(RangeFinder::Type::VL53L1X_Short);
  Log_Init();
}

void loop(void* parameter)
{  
  while(1)
  {
    float vel_x = vel.vel_x;  // x max 0.104f
    float vel_y = vel.vel_y;  // y max 0.104f
    float rad_z = vel.rad_z;  // z max 0.7f
    
    base->vel2rpm(vel_x, vel_y, rad_z);
    
    range_finder->update();
    
    char buf[100];
    sprintf(buf, "dist_cm: %d\r\n", range_finder->distance_cm());
    rt_kputs(buf);
  
    rt_thread_delay(50);
  }
}

} // extern "C"
