#include <entry.h>
#include "AP_Buffer.h"
#include "AP_Buffer_Ring.h"

using namespace rtthread;

AP_Buffer *AP_Buffer::_instance;

AP_Buffer::AP_Buffer()
: _backend(NULL)
, _buf()
{
  _instance = this;
}

void
AP_Buffer::init(buffer_type_t type)
{
  switch(type){
  case RING:{
    _backend = new AP_Buffer_Ring(*this, _buf._buffer);
    break;
  }
  case FIFO:{
    break;
  }
  }
}

void
AP_Buffer::write(const void *pBuffer, uint16_t size)
{
  if(_backend != NULL){
    _backend -> write(pBuffer, size);
  }
}

void
AP_Buffer::read(const void *pBuffer, void* to, uint16_t size)
{
  if(_backend != NULL){
    _backend -> read(pBuffer, to, size);
  }
}
