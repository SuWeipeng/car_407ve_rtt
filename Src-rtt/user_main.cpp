#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdlib.h>
#include "rtt_interface.h"
#include "AC_Base.h"
#include "Logger.h"
#include "AP_Buffer.h"

using namespace rtthread;

extern vel_target vel;
extern rt_device_t vcom;

Mecanum_4wd *base;
AP_Buffer *buffer;

extern "C" {
void setup(void)
{
  base = new Mecanum_4wd();
  buffer = new AP_Buffer();
  buffer->init(AP_Buffer::RING);
  Write_Test();
}

void loop(void* parameter)
{
  uint32_t cnt = 0;
  
  while(1)
  {
    float vel_x = vel.vel_x;  // x max 0.104f
    float vel_y = vel.vel_y;  // y max 0.104f
    float rad_z = vel.rad_z;  // z max 0.7f
    
    base->vel2rpm(vel_x, vel_y, rad_z);
    
    char c[1];
    uint8_t i;
    sprintf(c, "%d", cnt++ % 10);
    buffer->write(c,sizeof(c));
    if(cnt%2 == 0){
      i = buffer->read();
    }
    if(i>0){
      char buf[100];
      sprintf(buf, "buf:%s ,len:%d\r\n", buffer->read_buf_addr(), buffer->buf_len());
      rt_device_write(vcom, 0, buf, rt_strlen(buf));
    }
  
    rt_thread_delay(30);
  }
}

} // extern "C"
