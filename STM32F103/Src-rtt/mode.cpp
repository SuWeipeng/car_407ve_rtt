#include <entry.h>
#include "mode.h"

extern Mode             *car_mode;
extern ModeManual       *mode_manual;
extern ModeAuto         *mode_auto;
extern ModeROS          *mode_ros;
extern Mode::Number     current_mode;
extern Mode::Number     prev_mode;
extern Mode::ModeReason mode_reason;
extern uint8_t          mode_mav;

static Mode* mode_from_mode_num(const Mode::Number mode);
static void  notify_mode(const Mode::Number mode);
static Mode::Number num2mode(uint8_t num);

Mode*  mode_from_mode_num(const Mode::Number mode)
{
  Mode* ret = nullptr;
  
  switch ( mode ) {
  case Mode::Number::MAN:{
    ret = mode_manual;
    break;
  }
  case Mode::Number::AUTO:{
    ret = mode_auto;
    break;
  }
  case Mode::Number::ROS:{
    ret = mode_ros;
    break;
  }
  default:
    break;
  }
  
  return ret;
}

void notify_mode(const Mode::Number mode)
{
  switch (mode) {
  case Mode::Number::MAN:{
    break;
  }
  case Mode::Number::AUTO:{
    break;
  }
  case Mode::Number::ROS:{
    break;
  }
  default:
    break;
  }
}

Mode::Number num2mode(uint8_t num)
{
  Mode::Number ret = Mode::Number::MAN;
  
  switch (num) {
  case 0:{
    ret = Mode::Number::MAN;
    break;
  }
  case 1:{
    ret = Mode::Number::AUTO;
    break;
  }
  case 2:{
    ret = Mode::Number::ROS;
    break;
  }
  }
  
  return ret;
}

Mode::ModeReason num2reason(uint8_t reason)
{
  Mode::ModeReason ret = Mode::ModeReason::UNKNOWN;
  
  switch (reason) {
  case 0:{
    ret = Mode::ModeReason::UNKNOWN;
    break;
  }
  case 1:{
    ret = Mode::ModeReason::RC_SW;
    break;
  }
  case 2:{
    ret = Mode::ModeReason::ROS_COMMAND;
    break;
  }
  }
  
  return ret;
}

void update_mode()
{
  mode_mav = (uint8_t)current_mode;
  car_mode->run();
}

bool set_mode(Mode::Number mode, Mode::ModeReason reason)
{
  if (mode == current_mode){
    return true;
  }
  
  Mode *new_mode = mode_from_mode_num(mode);
  if (new_mode == nullptr) {
    return false;
  }
  
  prev_mode = current_mode;
  
  if (mode_from_mode_num(prev_mode)->exit()){
    if (new_mode->init()) {
      notify_mode(mode);
      car_mode     = new_mode;
      current_mode = mode;
      mode_reason  = reason;
    }  
  }
  
  return true;
}

rt_sem_t    mode_sem    = RT_NULL;
rt_mq_t     mode_mq     = RT_NULL;
rt_thread_t mode_thread = RT_NULL;

static uint8_t mode_msg[2];

extern "C"
void mode_thread_entry(void* parameter)
{
  rt_err_t uwRet = RT_EOK;
  while(1) {
    rt_sem_take(mode_sem, RT_WAITING_FOREVER);
    
    uwRet = rt_mq_recv(mode_mq,
                       mode_msg,
                       sizeof(mode_msg),
                       RT_WAITING_FOREVER);
    
    if(RT_EOK != uwRet) {
      rt_kprintf("mq recv error, code: 0x%lx\n", uwRet);
    } else {
      set_mode(num2mode(mode_msg[0]), num2reason(mode_msg[1]));
    }
    
    rt_thread_mdelay(1);
  }
}
