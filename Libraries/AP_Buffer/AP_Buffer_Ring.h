#ifndef __AP_BUFFER_RING_H__
#define __AP_BUFFER_RING_H__

#include "AP_Buffer_Backend.h"

class AP_Buffer_Ring : public AP_Buffer_Backend{
public:
  AP_Buffer_Ring(AP_Buffer &instance, const void* buffer);
  ~AP_Buffer_Ring(){};
  
  virtual void write(const void *pBuffer, uint16_t size);
  virtual void read(const void *pBuffer, void* to, uint16_t size);
  
private:
  const void* _head;
  const void* _tail;
};

#endif /* __AP_BUFFER_RING_H__ */
