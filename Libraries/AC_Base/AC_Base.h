#ifndef __AC_BASE_H__
#define __AC_BASE_H__

#include <stdint.h>

class AC_Base_Backend;

class AC_Base{
  friend class AC_Base_Backend;
  friend class Mecanum_4wd;
public:
  enum class Type : uint8_t {
    NONE         = 0,
    MECANUM_4WD  = 1, 
  };
  
  AC_Base(Type type);
  
  Type get_base_type() { return _type; }
  
  void init();
  void pct2rpm(float& pct_x, float& pct_y, float& pct_z);
  
#if defined(USE_RTTHREAD)
  void log_write_base();
#endif

private:
  static AC_Base*         _instance;
  AC_Base_Backend*        _backend;
  Type                    _type;
};
  
#endif /* __AC_BASE_H__ */