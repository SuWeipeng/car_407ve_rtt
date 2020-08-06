#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdlib.h>
#include "rtt_interface.h"
#include "AC_Base.h"
#include "mode.h"

using namespace rtthread;

AC_Base      *base;
Mode         *car_mode;
ModeManual   *mode_manual;
ModeAuto     *mode_auto;
ModeROS      *mode_ros;

Mode::Number     current_mode = Mode::Number::MAN;
Mode::Number     prev_mode    = Mode::Number::MAN;
Mode::ModeReason mode_reason  = Mode::ModeReason::UNKNOWN;

extern "C" {
void setup(void)
{
  base        = new AC_Base(AC_Base::Type::DIFF_2WD);
  mode_manual = new ModeManual();
  mode_auto   = new ModeAuto();
  mode_ros    = new ModeROS();
  car_mode    = mode_manual;
  
  base->init();
}

void loop(void* parameter)
{  
  while(1)
  {
    update_mode();
  
    rt_thread_delay(50);
  }
}

} // extern "C"
