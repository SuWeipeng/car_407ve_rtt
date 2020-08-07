#ifndef __AC_BASE_BACKEND_H__
#define __AC_BASE_BACKEND_H__

#include "AC_Base.h"
#include "AC_Base_Conf.h"

class AC_Base_Backend{
public:
  AC_Base_Backend(AC_Base &instance);
  
  virtual void pct2rpm(float& pct_x, float& pct_y, float& pct_z) = 0;
  virtual void pct2rpm(float& pct_x, float& pct_z) = 0;
  
#if defined(USE_RTTHREAD)
  virtual void log_write_base() {}
#endif
  
protected:
  AC_Base &_frontend;
};

#endif /* __AC_BASE_BACKEND_H__ */
