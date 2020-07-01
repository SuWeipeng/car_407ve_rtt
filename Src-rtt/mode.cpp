#include "mode.h"

extern Mode             *car_mode;
extern ModeManual       *mode_manual;
extern ModeAuto         *mode_auto;
extern ModeROS          *mode_ros;
extern Mode::Number     current_mode;
extern Mode::Number     prev_mode;
extern Mode::ModeReason mode_reason;

static Mode* mode_from_mode_num(const Mode::Number mode);
static void  notify_mode(const Mode::Number mode);

Mode*  mode_from_mode_num(const Mode::Number mode)
{
  Mode* ret = nullptr;
  
  switch ( mode ) {
  case Mode::Number::MAN:
    {
      ret = mode_manual;
      break;
    }
  case Mode::Number::AUTO:
    {
      ret = mode_auto;
      break;
    }
  case Mode::Number::ROS:
    {
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
  case Mode::Number::MAN:
    {
      break;
    }
  case Mode::Number::AUTO:
    {
      break;
    }
  case Mode::Number::ROS:
    {
      break;
    }
  default:
    break;
  }
}

void update_mode()
{
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
    }  
  }
  
  car_mode     = new_mode;
  current_mode = mode;
  mode_reason  = reason;
  
  return true;
}
