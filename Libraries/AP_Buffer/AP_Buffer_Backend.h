#ifndef __AP_BUFFER_BACKEND_H__
#define __AP_BUFFER_BACKEND_H__

#include "AP_Buffer.h"

class AP_Buffer_Backend{
public:
  AP_Buffer_Backend(AP_Buffer &buffer);
  ~AP_Buffer_Backend(){};
  
protected:
  AP_Buffer &_frontend;
};

#endif /* __AP_BUFFER_BACKEND_H__ */