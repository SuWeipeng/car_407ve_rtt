#include "AP_Buffer.h"

AP_Buffer *AP_Buffer::_instance;

AP_Buffer::AP_Buffer()
{
  _instance = this;
}