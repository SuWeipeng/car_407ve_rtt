#ifndef __AP_BUFFER_RING_H__
#define __AP_BUFFER_RING_H__

#include "AP_Buffer_Backend.h"

class AP_Buffer_Ring : public AP_Buffer_Backend{
public:
  AP_Buffer_Ring(AP_Buffer &buffer);
  ~AP_Buffer_Ring(){};
};

#endif /* __AP_BUFFER_RING_H__ */