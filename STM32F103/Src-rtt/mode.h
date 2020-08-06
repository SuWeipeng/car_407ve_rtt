#pragma once

#include <stdint.h>

class Mode {
public:
  enum class Number : uint8_t {
    MAN          = 0, // manual mode
    AUTO         = 1, // auto mode 
    ROS          = 2, // ros mode
  };
  enum class ModeReason : uint8_t {
    UNKNOWN,
    RC_SW,
    ROS_COMMAND,
  };

  Mode(void){};
  
  Mode(const Mode &other)      = delete;
  Mode &operator=(const Mode&) = delete;  
  
  virtual bool init(){
    return true;
  }
  virtual bool exit(){
    return true;
  }
  
  virtual void run() = 0;
};

class ModeManual : public Mode {
public:
  using Mode::Mode;
  
  void run() override;
};

class ModeAuto : public Mode {
public:
  using Mode::Mode;
  
  void run() override;
};

class ModeROS : public Mode {
public:
  using Mode::Mode;
  
  void run() override;
};

void  update_mode();
bool  set_mode(Mode::Number mode, Mode::ModeReason reason);
