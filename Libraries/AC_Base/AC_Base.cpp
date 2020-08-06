#if defined(STM32F407xx)
#include "AP_Buffer.h"
#endif
#include "Mecanum_4wd.h"
#include "Diff_2wd.h"

AC_Base *AC_Base::_instance;

AC_Base::AC_Base(Type type)
: _backend(nullptr)
, _type(type)
{
  _instance = this;
}

void 
AC_Base::init()
{
  switch(_type){
    case AC_Base::Type::MECANUM_4WD:{
      _backend = new Mecanum_4wd(*this);
      break;
    }
    case AC_Base::Type::DIFF_2WD:{
      _backend = new Diff_2wd(*this);
      break;
    }
    default:{
      break;
    }
  }
}

void 
AC_Base::pct2rpm(float& pct_x, float& pct_y, float& pct_z)
{
  if(_backend != nullptr){
    _backend->pct2rpm(pct_x, pct_y, pct_z);
  }
}

#if defined(USE_RTTHREAD) && defined(STM32F407xx)
void 
AC_Base::log_write_base()
{
  if(_backend != nullptr){
    _backend->log_write_base();
  }
}
#endif